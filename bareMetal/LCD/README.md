## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)

## General info
* To drive the LCD, perform the following:
	* Download the 'lcd.c' and 'lcd.h' files from this folder
	* Add the files into your STM32CubeIDE project. You can do this by the drag & drop feature.
 		* In your file browser select the files and drop them in the project window
			* Drop the 'lcd.h' file in the Inc/ folder
			* Drop the ‘lcd.c’ file in the Src/ folder 
	* The 'lcd.h' file contains all the function prototypes and pin definitions.
	* The 'lcd.c' file contains the functions needed to initialize and drive the LCD1602 (clear the display, move the cursor, write a character, write a string, etc.)
		* In this file, you will need to implement your own delays. Pay attention to the desired times.
	
## Technologies
Project is created with:
* Lorem version: 12.3
* Ipsum version: 2.33
* Ament library version: 999
	
## Setup
To run this project, install it locally using npm:

```
$ cd ../lorem
$ npm install
$ npm start
```
