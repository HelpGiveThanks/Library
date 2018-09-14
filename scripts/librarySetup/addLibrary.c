September 10, 2018 16:35:41 Library.fmp12 - addLibrary -1-
librarySetup: addLibrary
#
#
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#!!!!!!!!!! NOTE !!!!!!!!!!!!!
#This script needs to be kept identical to the
#same script in all HGT apps.
#
#
#If on an iOS device ...
If [ Get ( SystemPlatform ) = 3 ]
#
#Tell user how to add a library.
Show Custom Dialog [ Message: "To add libraries to the All Apps menu, 1) click the circled v in the upper-left corner, and 2)
select launch center. 3) In the bottom of the next window, click Device. 4) Now click on any library file to add it to the All
Apps menu."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "FYI: An open library deleted from this list using the X button, cannot be added back to it until the library is closed and re-opened."; Default Button: “OK”, Commit: “Yes” ]
#
#Go to field is needed to insure first library
#added shows up after adding it.
Go to Field [ ]
#
#Halt the script so that the pause script
#command is disabled which will allow the user
#to click the blue circled arrow in the upper-
#left-hand corner of an iOS device.
Halt Script
#
#
#If on an desktop/laptop computer ...
Else
#
#Tell a user how to add a library.
Show Custom Dialog [ Message: "The Libraries folder will now open. To add libraries to the All Apps menu, double-click library
files in it and its subfolders. (A library must be re-added if moved or if its name is changed.)"; Default Button: “OK”, Commit:
“Yes” ]
Show Custom Dialog [ Message: "FYI: A open library deleted from this list, using the X button, cannot be added back to the list
until it is closed, and then re-opened."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#Open the folder where all libraries must be stored.
Open URL [ Substitute (
Left ( MemorySwitch::helpPath ; Length ( MemorySwitch::helpPath ) -
Case ( Middle ( Right ( MemorySwitch::helpPath ; 6 ) ; 0 ; 1 ) = "." ; 11 ;
 Middle ( Right ( MemorySwitch::helpPath ; 5 ) ; 0 ; 1 ) = "." ; 10 ;
 Middle ( Right ( MemorySwitch::helpPath ; 4 ) ; 0 ; 1 ) = "." ; 9 ;
 Middle ( Right ( MemorySwitch::helpPath ; 3 ) ; 0 ; 1 ) = "." ; 8 ) )
& "/Libraries"
 ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Left ( MemorySwitch::helpPath ; Length ( MemorySwitch::helpPath ) -
Case ( Middle ( Right ( MemorySwitch::helpPath ; 6 ) ; 0 ; 1 ) = "." ; 11 ;
 Middle ( Right ( MemorySwitch::helpPath ; 5 ) ; 0 ; 1 ) = "." ; 10 ;
 Middle ( Right ( MemorySwitch::helpPath ; 4 ) ; 0 ; 1 ) = "." ; 9 ;
 Middle ( Right ( MemorySwitch::helpPath ; 3 ) ; 0 ; 1 ) = "." ; 8 ) )
& "/Libraries" ]
[ No dialog ]
End If
#
#Open the folder where the libraries folder is
#supposed to be if the script step above fails to
#open this folder.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The Libraries folder name has been changed, or this folder has been moved. It belongs in the
same folder as the Help, and reference files."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Open the folder it belongs in, so you can fix its name, or put it back in this folder?"; Default
Button: “yes”, Commit: “Yes”; Button 2: “no”, Commit: “No” ]
If [ Get (LastMessageChoice) = 1 ]
Open URL [ Substitute (
Left ( MemorySwitch::helpPath ; Length ( MemorySwitch::helpPath ) -
Case ( Middle ( Right ( MemorySwitch::helpPath ; 6 ) ; 0 ; 1 ) = "." ; 11 ;
 Middle ( Right ( MemorySwitch::helpPath ; 5 ) ; 0 ; 1 ) = "." ; 10 ;
 Middle ( Right ( MemorySwitch::helpPath ; 4 ) ; 0 ; 1 ) = "." ; 9 ;
 Middle ( Right ( MemorySwitch::helpPath ; 3 ) ; 0 ; 1 ) = "." ; 8 ) )
 ; " " ; "%20" ) ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Left ( MemorySwitch::helpPath ; Length ( MemorySwitch::helpPath ) -
Case ( Middle ( Right ( MemorySwitch::helpPath ; 6 ) ; 0 ; 1 ) = "." ; 11 ;
 Middle ( Right ( MemorySwitch::helpPath ; 5 ) ; 0 ; 1 ) = "." ; 10 ;
 Middle ( Right ( MemorySwitch::helpPath ; 4 ) ; 0 ; 1 ) = "." ; 9 ;
 Middle ( Right ( MemorySwitch::helpPath ; 3 ) ; 0 ; 1 ) = "." ; 8 ) ) ]
[ No dialog ]
End If
End If
End If
#
#Go to field is needed to insure first library
#added shows up after adding it.
Go to Field [ ]
Refresh Window
[ Flush cached join results; Flush cached external data ]
#
#Halt the script so that the pause script
#command is disabled which will allow the user
#to open library files.
Halt Script
#
#
