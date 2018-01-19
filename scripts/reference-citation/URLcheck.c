January 18, 2018 15:39:26 Library.fmp12 - seeIfFilenameIsValid -1-
reference: seeIfFilenameIsValid
#
#This stop variable is set by the
#exitAndSeeIfFileNameIsValid which is
#triggered when the user leaves the filename
#field. It prevents a logic loop.
If [ $$stopFileNameCheck = 1 ]
Exit Script [ ]
End If
#
#These characters ? # / ; : prevent the
#Library from opening files. Give the user the
#opportunity to change their file name so it
#will open using FileMaker's open file
#script step.
If [ Filter ( reference::fileName ; "?" ) = "?" or
Filter ( reference::fileName ; "#" ) = "#" or
Filter ( reference::fileName ; ";" ) = ";" or
Filter ( reference::fileName ; "/" ) = "/" or
Filter ( reference::fileName ; ":" ) = ":" ]
Show Custom Dialog [ Message: "These characters ? # / ; : prevent the Library from opening files. Change this file's name
(remove these characters) both on the harddrive and here if you want the 'file' button above to open your file."; Default Button:
“OK”, Commit: “Yes” ]
Go to Field [ reference::fileName ]
End If
