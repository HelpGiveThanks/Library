July 24, 2018 16:39:49 Library.fmp12 - setupReference_New -1-
librarySetup: setupReference_New
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
Show Custom Dialog [ Message: "NOTE: Create about-the-library records to share a library filled with templates, information, and
reference records to help others track a process, learning something, etc."; Default Button: “cancel”, Commit: “Yes”; Button 2:
“OK”, Commit: “No” ]
#
#If they click cancel, then exit the script.
If [ Get (LastMessageChoice) = 1 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#Encourage user to improve any library
#setup the use.
Show Custom Dialog [ Message: "1) Make a short note about your library configuration's purpose, or your improvements,
modifications, etc. to another's configuration. 2) Give yourself credit. 3) Share!"; Default Button: “cancel”, Commit: “Yes”; Button
2: “OK”, Commit: “No” ]
#
#If they click cancel, then exit the script.
If [ Get (LastMessageChoice) = 1 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#Create new setup reference.
New Record/Request
Set Field [ librarySetupReferenceMain::kcreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ librarySetupReferenceMain::name; "Library Configuration Name" ]
#
Set Field [ librarySetupReferenceMain::creatorName; "FirstName LastName" ]
Set Field [ librarySetupReferenceMain::version; "1" ]
#
#Go to edit setup reference window.
Set Variable [ $$newSetupReference; Value:1 ]
Perform Script [ “setupReference_GoToPortalReferenceRevieworWebsite” ]
#
#
#
