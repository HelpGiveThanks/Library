July 20, 2018 17:25:40 Library.fmp12 - allAppsMenu -1-
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
#Pause script so user has to close this window
#before they are allowed to anything else.
Pause/Resume Script [ Indefinitely ]
