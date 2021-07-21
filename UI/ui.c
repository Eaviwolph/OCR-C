#include <gtk/gtk.h>
#include "ui.h"

// Structure of the graphical user interface.
typedef struct UserInterface
{
  GtkWindow* window;              // Main window
  GtkButton* start_button;        // Start button
  GtkButton* load_button;
  GtkButton* rotr_button;
  GtkButton* rotl_button;
  GtkButton* contrp_button;
  GtkButton* contrm_button;
  GtkTextBuffer* buffer;    // Training check box
  GtkImage* picture;
  SDL_Surface* image;
  SDL_Surface* modifiedimage;
  int degree;
  double contrast;
} UserInterface;



char* OpenExp(UserInterface *ui)
{
  GtkWidget *dialog; gint res; char *filename = "";
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  dialog = gtk_file_chooser_dialog_new ("Open File",
					ui->window,
					action,
					"_Cancel",
					GTK_RESPONSE_CANCEL,
					"_Open",
					GTK_RESPONSE_ACCEPT,
					NULL);
  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
    {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      filename = gtk_file_chooser_get_filename (chooser);
      gtk_widget_destroy (dialog);
    }

  gtk_widget_destroy (dialog);
  return filename;
}
  
void on_load(GtkButton *button, gpointer user_data)
{
  UserInterface *ui = user_data;
  (void)(button);
  
  char* filename = OpenExp(ui);
  if(strcmp(filename,"") != 0)
    {
      if(ui->image != NULL)
	{
	  SDL_FreeSurface(ui->image);
	}
      if(ui->modifiedimage != NULL)
	{
	  SDL_FreeSurface(ui->modifiedimage);
	  ui->modifiedimage = NULL;
	}
      ui->image = SDL_LoadBMP(filename);
      SDL_SaveBMP(ui->image, "img");
      gtk_image_set_from_file(ui->picture, "img");
    }
}

void on_rotl(GtkButton *button, gpointer user_data)
{
  UserInterface *ui = user_data;
  (void)(button);
  if(ui->image != NULL)
    {
      ui->degree = (ui->degree - 5)%360;
      ui->modifiedimage = RotCentDeg(ui->image, ui->degree);
      Contrast(ui->modifiedimage, ui->contrast);
      SDL_SaveBMP(ui->modifiedimage, "img");
      gtk_image_set_from_file(ui->picture, "img");
    }
}

void on_rotr(GtkButton *button, gpointer user_data)
{
  UserInterface *ui = user_data;
  (void)(button);
  if(ui->image != NULL)
    {
      ui->degree = (ui->degree + 5)%360;
      ui->modifiedimage = RotCentDeg(ui->image, ui->degree);
      Contrast(ui->modifiedimage, ui->contrast);
      SDL_SaveBMP(ui->modifiedimage, "img");
      gtk_image_set_from_file(ui->picture, "img");
    }
}

void on_contrastp (GtkButton *button, gpointer user_data)
{
  UserInterface *ui = user_data;
  (void)(button);
  if(ui->image != NULL)
    {
      ui->modifiedimage = RotCentDeg(ui->image, ui->degree);
      ui->contrast += 0.1;
      Contrast(ui->modifiedimage, ui->contrast);
      SDL_SaveBMP(ui->modifiedimage, "img");
      gtk_image_set_from_file(ui->picture, "img");
    }
}

void on_contrastm (GtkButton *button, gpointer user_data)
{
  UserInterface *ui = user_data;
  (void)(button);
  if(ui->image != NULL)
    {
      ui->modifiedimage = RotCentDeg(ui->image, ui->degree);
      ui->contrast -= 0.1;
      if(ui->contrast<0)
	{
	  ui->contrast = 0;
	}
      Contrast(ui->modifiedimage, ui->contrast);
      SDL_SaveBMP(ui->modifiedimage, "img");
      gtk_image_set_from_file(ui->picture, "img");
    }
}


void cut(char* source, char* dest)
{
  int j = 0;

  for (int i = 0; source[i] != '\0'; i++)
    {
      if (source[i] != ' ' && source[i] != '\n')
	{
	  dest[j] = source[i];
	  j++;
	}
    }
  dest[j] = '\0';
}

char* getBufferlines(UserInterface *ui)
{
  char* buffertext;
  GtkTextIter start;
  GtkTextIter end;
  gtk_text_buffer_get_start_iter (ui->buffer, &start);
  gtk_text_buffer_get_end_iter (ui->buffer, &end);
  buffertext = gtk_text_buffer_get_text (ui->buffer, &start, &end, FALSE);
  return buffertext;
}

void initText(char* text, int x)
{
  for(int i = 0; i < x-1; i++)
    {
      text[i] = ' ';
    }
  text[x-1] = '\0';
}

// Ouvre l'explorateur de fichiers                          FAIT
// Recupérer le fil d'Ariane                                FAIT
// Afficher le résultat obtennu dans une area
void on_start(GtkButton *button, gpointer user_data)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  UserInterface *ui = user_data;
  (void)(button);
  if(ui->image != NULL)
    {
      if(ui->modifiedimage == NULL)
	ui->modifiedimage = ui->image;
      char*source = getBufferlines(ui);
      char torecognize[strlen(source)]; cut(source, torecognize);
      int x = 125;
      if(strcmp(torecognize,"") != 0)
	x = strlen(torecognize) + strlen(torecognize) / 4;
      char textBuffer[x]; initText(textBuffer, x);
      IMGTreatment(ui->modifiedimage, torecognize, textBuffer);
      gtk_text_buffer_set_text (ui->buffer, textBuffer, strlen(textBuffer));
      if(ui->modifiedimage == ui->image)
	ui->modifiedimage = NULL;
    }
  SDL_Quit();
}

void InitUI (GtkBuilder* builder, UserInterface* ui)
{
  // Gets the widgets.
  GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.ui"));
  GtkButton* start_button = GTK_BUTTON(gtk_builder_get_object(builder, "start_button"));
  GtkButton* load_button = GTK_BUTTON(gtk_builder_get_object(builder, "load_button"));
  GtkButton* rotr_button = GTK_BUTTON(gtk_builder_get_object(builder, "rotr_button"));
  GtkButton* rotl_button = GTK_BUTTON(gtk_builder_get_object(builder, "rotl_button"));
  GtkButton* contrp_button = GTK_BUTTON(gtk_builder_get_object(builder, "contrast+"));
  GtkButton* contrm_button = GTK_BUTTON(gtk_builder_get_object(builder, "contrast-"));
  GtkTextBuffer* buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "TextBuffer"));
  GtkImage* picture = GTK_IMAGE(gtk_builder_get_object(builder, "Picture"));
  // Creates the "ui" structure.
  ui->window = window;
  ui->start_button = start_button;
  ui->load_button = load_button;
  ui->rotr_button = rotr_button;
  ui->rotl_button = rotl_button;
  ui->contrp_button = contrp_button;
  ui->contrm_button = contrm_button;
  ui->buffer = buffer;
  ui->picture = picture;
  ui->image = NULL;
  ui->modifiedimage = NULL;
  ui->degree = 0;
  ui->contrast = 1;
}


int ui ()
{
  
  // Initializes GTK.
  gtk_init(NULL, NULL);
  // Constructs a GtkBuilder instance.
  GtkBuilder* builder = gtk_builder_new ();
  // Loads the UI description. (Exits if an error occurs.)
  GError* error = NULL;
  if (gtk_builder_add_from_file(builder, "UI/ui.glade", &error) == 0)
    {
      g_printerr("Error loading file: %s\n", error->message);
      g_clear_error(&error);
      return 1;
    }
  UserInterface ui; InitUI (builder, &ui);
  // Connects event handlers.
  g_signal_connect(ui.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  //g_signal_connect(area, "draw", G_CALLBACK(on_draw), &game);
  g_signal_connect(ui.start_button, "clicked", G_CALLBACK(on_start), &ui);
  g_signal_connect(ui.load_button, "clicked", G_CALLBACK(on_load), &ui);
  g_signal_connect(ui.rotr_button, "clicked", G_CALLBACK(on_rotr), &ui);
  g_signal_connect(ui.rotl_button, "clicked", G_CALLBACK(on_rotl), &ui);
  g_signal_connect(ui.contrp_button, "clicked", G_CALLBACK(on_contrastp), &ui);
  g_signal_connect(ui.contrm_button, "clicked", G_CALLBACK(on_contrastm), &ui);
  
  // Runs the main loop.
  gtk_main();
  if(ui.image != NULL)
    {
      SDL_FreeSurface(ui.image);
    }
  if(ui.modifiedimage != NULL)
    {
      SDL_FreeSurface(ui.modifiedimage);
    }
  // Exits.
  return 0;
}

