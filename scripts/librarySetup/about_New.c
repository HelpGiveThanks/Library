July 25, 2018 23:45:21 Library.fmp12 - about_New -1-
librarySetup: about_New
#
#
#This script is for creating a curator record.
If [ TEMP::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible for creating new records) by clicking the node button.";
Default Button: “OK”, Commit: “Yes” ]
Halt Script
End If
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#Make sure user understands the reason
#to create a setup reference record.
Show Custom Dialog [ Message: "NOTE: Create about-the-library records to share a library filled with your templates, information, and
reference records to help others learn, research, follow a checklist, etc."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”,
Commit: “No” ]
#
#If they click cancel, then exit the script.
If [ Get (LastMessageChoice) = 2 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#Encourage user to improve any library
#setup the use.
Show Custom Dialog [ Message: "Make a short note about your library configuration's purpose, or your improvements, modifications,
etc. to another's configuration."; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If they click cancel, then exit the script.
If [ Get (LastMessageChoice) = 2 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#Create new setup reference.
New Record/Request
Set Field [ aboutLibraryMain::kcreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ aboutLibraryMain::name; "Library Configuration Name" ]
#
Set Field [ aboutLibraryMain::creatorName; "FirstName LastName" ]
Set Field [ aboutLibraryMain::version; "1" ]
#
#Go to edit setup reference window.
Set Variable [ $$newSetupReference; Value:1 ]
Perform Script [ “about_GoToConfigurationRevieworWebsite” ]
#
#
#
