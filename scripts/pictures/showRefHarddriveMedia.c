January 15, 2018 17:32:50 Library.fmp12 - showRefHarddriveMedia -1-
pictures: showRefHarddriveMedia
#
#
#Inform user if they have not entered a FileName or
#selected the file's location: main, other, x.
If [ reference::fileName = "" and reference::kfileLocation = "" and reference::picture = "" and reference::showMedia[2] ≠ ""
 or
reference::fileName = "" and reference::kfileLocation = "" and reference::picture = "Replace Me. Media Required" and reference::
showMedia[2] ≠ "" ]
Set Field [ reference::showMedia[2]; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Enter a filename and select a file location below to see HDDmedia displayed here."; Default
Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
#
#Inform user if they have not entered a FileName.
Else If [ reference::fileName = "" and reference::picture = "" and reference::showMedia[2] ≠ ""
 or
reference::fileName = "" and reference::picture = "Replace Me. Media Required" and reference::showMedia[2] ≠ "" ]
Set Field [ reference::showMedia[2]; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Enter a filename below to see HDDmedia displayed here."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
#
#Inform user if they have not selected
#the file's location: main, other, x.
Else If [ reference::kfileLocation = "" and reference::picture = "" and reference::showMedia[2] ≠ ""
 or
reference::kfileLocation = "" and reference::picture = "Replace Me. Media Required" and reference::showMedia[2] ≠ "" ]
Set Field [ reference::showMedia[2]; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Select a file location to see HDDmedia displayed here."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
#
#Inform user if they have not selected
#the file's location path.
Else If [ FilterValues ( reference::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ and reference::kfolderpath = "" and
reference::picture = "" and reference::showMedia[2] ≠ ""
 or
FilterValues ( reference::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ and reference::kfolderpath = "" and
reference::picture = "Replace Me. Media Required" and reference::showMedia[2] ≠ "" ]
Set Field [ reference::showMedia[2]; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Select the media's file-path tag to see HDDmedia displayed here."; Default Button: “OK”,
Commit: “Yes” ]
Exit Script [ ]
#
#Inform user that the picture field is filled and must be
#cleared before they can display other media, unless
#the picture field is filled with a placeholder, in which
#case delete the place holder and show the
#other media.
Else If [ reference::picture ≠ "" ]
If [ reference::picture = "Replace Me. Media Required" ]
Set Field [ reference::picture; "" ]
Go to Field [ ]
Exit Script [ ]
End If
Set Field [ reference::showMedia[2]; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "You can click to view HDDmedia only if you first delete the current picture. 1) Click on the
picture. 2) Click 'X' in the popup window that opens."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
#
#Check if file is a media that will display:
#IMAGE — bmp, gif, jpeg, jpg, png, psd, sgi,
#tga, tif, tiff; MOVIE — mp4, m4v.
Else If [ //Check if file is a media that will display.
0 = (
reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "bmp"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "gif"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 4 ) = "jpeg"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "jpg"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "png"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "psd"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "sgi"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tga"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tif"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 4 ) = "tiff"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "mp4"
or reference::kfileLocation = "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "m4v"
or
reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "bmp"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "gif"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 4 ) = "jpeg"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "jpg"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "png"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "psd"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "sgi"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tga"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tif"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 4 ) = "tiff"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "mp4"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "m4v") ]
#
#If the media file is not displayable, inform the
#user so they can convert it to a format that
#will display.
Set Field [ reference::showMedia[2]; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Your file name must include one of these file extensions to be displayed: IMAGE = bmp, gif,
jpeg, jpg, png, psd, sgi, tga, tif, tiff; MOVIE = mp4, m4v."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#Remove check from web media box if checked
#so HDD media will show up.
Set Field [ reference::showMedia; "" ]
Go to Field [ ]
#
#
#If media is in use then inform user if they
#attempt to edit it.
If [ reference::showMedia = "" and reference::showMedia[2] = "" ]
Set Variable [ $$showRefURLmedia; Value:2 ]
Perform Script [ “CHUNK_checkIfReferencePicIsInUse” ]
Go to Field [ ]
Set Variable [ $$showRefURLmedia ]
If [ reference::picture = "Replace Me. Media Required" ]
Perform Script [ “showCitationPicture1inNewWindow” ]
End If
End If
#
