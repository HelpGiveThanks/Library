July 24, 2018 17:37:28 Library.fmp12 - about_GoToConfigurationRevieworWebsite -1-
librarySetup: about_GoToConfigurationRevieworWebsite
#
#
#If there are no user created references, then tell user
#how to download a fresh copy of the library app.
If [ Get (FoundCount) = 0 ]
Show Custom Dialog [ Message: "This library when downloaded was an empty, unmodified version of the applicaiton, without
any user created notes (Learn records), references, or test templates in it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#Capture variables needed when user clicks
#the review button, or clicks on a portal
#reference record.
If [ Get ( ActiveFieldName ) = "" ]
Set Variable [ $record; Value:aboutLibraryMain::_LaboutLibrary ]
Set Variable [ $password; Value:aboutLibraryMain::password ]
Set Variable [ $url; Value:aboutLibraryMain::URL ]
Else
Set Variable [ $record; Value:aboutLibraryReferencePortal::_LaboutLibrary ]
Set Variable [ $password; Value:aboutLibraryReferencePortal::password ]
Set Variable [ $url; Value:aboutLibraryReferencePortal::URL ]
Set Variable [ $portal; Value:1 ]
End If
#
#Exit any field user was in.
Go to Field [ ]
#
#
#Ask the user if they want to view this library'e
#record, edit it, or go to the library's website,
#BUT ONLY IF the record has a URL, and the
#user click on a portal record. (The main
#record has a button to go to the web, so it
#would be redundant to ask them if they want
#to go to the web when they just clicked the
#review button insetad of the web button.)
If [ $URL ≠ "" and $portal ≠ "" ]
Show Custom Dialog [ Message: "Review library information, or go to library website?"; Default Button: “cancel”, Commit: “Yes”;
Button 2: “review”, Commit: “No”; Button 3: “go”, Commit: “No” ]
End If
#
#
#If they click cancel, then exit the script.
If [ Get (LastMessageChoice) = 1 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#
#If they click go, then go (in the portal
#message dialogue box) to the library's
#website.
If [ Get (LastMessageChoice) = 3 ]
Open URL [ aboutLibraryReferencePortal::URL ]
[ No dialog ]
Go to Field [ ]
Exit Script [ ]
End If
#
#
#Close a Review Reference window that
#might be open due to a script interruption.
Close Window [ Name: "About"; Current file ]
#
#Open an Review Reference window.
New Window [ Name: "About"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
#
#If there is no password, go the review layout
#with an edit button, otherwise go to the
#review layout with no edit button.
If [ $password = "" ]
Go to Layout [ “aboutLibraryReviewUnlocked” (aboutLibraryMain) ]
Else
Go to Layout [ “aboutLibraryReviewLocked” (aboutLibraryMain) ]
End If
#
#Adjust window size and postion (for
#iDevice users), and then find just the
#record the user is interested in reviewing.
Adjust Window
[ Resize to Fit ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight) ]
Enter Find Mode [ ]
Set Field [ aboutLibraryMain::_LaboutLibrary; $record ]
Perform Find [ ]
#
#
#If this script was triggered by the
#newSetupReference script, then
#go to the edit layout, otherwise
#stay on the review layout.
If [ $$newSetupReference ≠ "" ]
Set Variable [ $$newSetupReference ]
Go to Layout [ “aboutLibraryEdit” (aboutLibraryMain) ]
Set Window Title [ Current Window; New Title: "Edit About" ]
#
#Tell user why the must enter their
#name again, when they used their
#node record to create this record.
Go to Field [ aboutLibraryMain::name ]
Show Custom Dialog [ Message: "NOTE: The creator name field is not filled in because unlike node tags, it needs to be in
FirstName LastName order, like the author's name on the cover of a book."; Default Button: “OK”, Commit: “Yes” ]
Go to Field [ aboutLibraryMain::name ]
End If
#
#Pause the script to prevent the user doing
#anything else until they have closed this
#review window.
Pause/Resume Script [ Indefinitely ]
#
#Just in case, close this window if the user
#hits the continue button somehow.
Close Window [ Current Window ]
Exit Script [ ]
#
#
