January 18, 2018 14:50:09 Library.fmp12 - SeeIfFileNameIsValidAndCanBeDisplayed -1-
reference: SeeIfFileNameIsValidAndCanBeDisplayed
#
#If more than one box is checked, tell user to
#remove check from the other box.
If [ ValueCount ( reference::kfileLocation ) = 3 ]
Show Custom Dialog [ Message: "Please uncheck two of the folders — main, other, x — as only one folder should be checked at
a time."; Default Button: “OK”, Commit: “Yes” ]
Else If [ ValueCount ( reference::kfileLocation ) > 1 ]
Show Custom Dialog [ Message: "Please uncheck one of the folders — main, other, x — as only one folder should be checked at
a time. (In a future update this will be fixed, so that you can only check one at a time.)"; Default Button: “OK”, Commit: “Yes” ]
End If
#
#If this a physical location then
#don't run this script.
If [ tagRefFolderPath::kfileORkTestItemCreatorNode = 1 ]
Exit Script [ ]
End If
#
#Prevents a logic loop. This script is triggered
#when the user leaves the filename field. If
#there is a problem detected by this script it
#will enter and exit this same field thus
#triggering itself = logic loop.
If [ $$stopFilenameCheck = 1 ]
Set Variable [ $$stopFilenameCheck ]
Halt Script
End If
#
#First see if the filename is valid.
Perform Script [ “seeIfFilenameIsValid” ]
#
#Check if file has a file extension.
If [ Left ( Right ( reference::fileName ; 4 ) ; 1 ) = "." or
Left ( Right ( reference::fileName ; 5 ) ; 1 ) = "." or
Left ( Right ( reference::fileName ; 6 ) ; 1 ) = "." or
Left ( Right ( reference::fileName ; 7 ) ; 1 ) = "." or
Left ( Right ( reference::fileName ; 8 ) ; 1 ) = "." or
Left ( Right ( reference::fileName ; 9 ) ; 1 ) = "." or
Left ( Right ( reference::fileName ; 10 ) ; 1 ) = "." or
Left ( Right ( reference::fileName ; 11 ) ; 1 ) = "." ]
#
#If it is displayable, then exit the field and halt
#this script.
Go to Field [ ]
#
#The halt script step exits any field the user
#may have entered into when clicking away
#from this field.
Halt Script
#
#If the media file is not displayable, inform the
#user so they can convert it to a format that
#will display.
Else
Show Custom Dialog [ Message: "The 'file' button can only open files that end with a period " & Quote ( "." ) & " followed by a file
extension: DOCUMENT: doc, html, ods, pdf, txt, webarchive; IMAGE = bmp, gif, jpeg, jpg, png, psd, sgi, tga, tif, tiff; MOVIE =
mp4, m4v."; Default Button: “Fix”, Commit: “Yes”; Button 2: “Don't Fix”, Commit: “No” ]
#
#If they decide to fix the file, then stay in the
#field and wait for the new file type extension
#to be entered.
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $$stopFilenameCheck; Value:1 ]
Go to Field [ ]
Go to Field [ reference::fileName ]
#
#If the user decides not to fix the file format,
#then exit the field and halt this script.
Else
Go to Field [ ]
#
#The halt script step exits any field the user
#may have entered into when clicking away
#from this field.
Halt Script
End If
End If
#
