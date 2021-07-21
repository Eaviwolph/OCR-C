# OCR-C
An Optical Character Recognition coded in C made as a project for EPITA

# English
This project is compilable on Linux with sdl2 lib installed.  

To compile the project: $ make  
To clean the project: $ make clean  

.\main to start the project,  
Usage: main [OPTION]  
Options:  
* XOR -> XOR training
* Image "File.bmp" -> Image tests
* Cut -> Cuts matrix tests

CharDetecor include the cutting managment of the picture  
IMGtreatment include the treatment of the picture  
NeuralSystem include the neural network (xor for now)  

# Français
Ce projet est compilable sur Linux avec la librairie sdl2 installée.  

Pour compiler le projet: $ make
Pour clean le projet : $make clean

.\main pour lancer le projet,
Usage: main [OPTION]
Options:
* XOR -> XOR training
* Image "File.bmp" -> Image tests
* Cut -> Cuts matrix tests

CharDetecor comprend la gestion du découpage de l'image
IMGtreatment comprend le traitement de l'image
NeuralSystem comprend le systeme de neurones (le xor pour l'instant)
