September 10, 2018 16:34:56 Library.fmp12 - allAppsMenu -1-
librarySetup: allAppsMenu
#PURPOSE go to all solutions menu.
#
#
#Set variable that will close this other apps menu
#when the user selectes a new database, and
Set Variable [ $$otherApps; Value:1 ]
#
#1 go to the edit/create layout and show all users.
Close Window [ Name: "All Apps"; Current file ]
New Window [ Name: "All Apps"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
Go to Layout [ “allApps” (tempSetup) ]
Show All Records
#
#Size window to 100%
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
Adjust Window
[ Resize to Fit ]
#
#If no libraries are detected then tell user why.
If [ MemorySwitch::name = "" ]
#
#If on an iOS device ...
If [ Get ( SystemPlatform ) = 3 ]
#
#Tell user how to add a library.
Show Custom Dialog [ Message: "To add libraries to the All Apps menu, 1) click the circled v in the upper-left corner, and 2)
select launch center. 3) In the bottom of the next window, click Device. 4) Now click on any library file to add it to the All
Apps menu."; Default Button: “OK”, Commit: “Yes” ]
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
Show Custom Dialog [ Message: "To add libraries to the All Apps menu, click the add button, and then double-click on any
library files that you wish to add (in the folder that will open after clicking the add button)."; Default Button: “OK”, Commit:
“Yes” ]
End If
End If
#
#Refresh to the window to update the libraries
#list, otherwise it might show libraries that have
#been deleted.
Refresh Window
#
#
#Pause script so user has to close this window
#before they are allowed to anything else.
Pause/Resume Script [ Indefinitely ]
