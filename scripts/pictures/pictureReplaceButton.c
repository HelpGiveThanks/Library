January 15, 2018 17:35:37 Library.fmp12 - pictureReplaceButton -1-
pictures: pictureReplaceButton
#
#
#If record is locked, which all default
#copyright symbols used for locked
#copyright tags are, then exit the script.
If [ reference::lock = "lock" ]
Show Custom Dialog [ Message: "This record is used by default copyright tags and so is locked."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
End If
#
#
#If the primary node for this record is locked
#then exit the script.
If [ tagTLNodePrimary::orderOrLock ≠ "" or $$PictureOnReportLayout ≠ "" ]
If [ tagTLNodePrimary::orderOrLock = "0" ]
Show Custom Dialog [ Message: "This Learn record's creator — " & tagTLNodePrimary::tag & " — is locked. To unlock, A)
go back to the setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button:
“OK”, Commit: “No” ]
Else If [ tagTLReportNodePrimary::orderOrLock = "0" ]
Show Custom Dialog [ Message: "This Learn record's creator — " & tagTLReportNodePrimary::tag & " — is locked. To
unlock, A) go back to the setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password.";
Default Button: “OK”, Commit: “No” ]
End If
Exit Script [ ]
End If
#
#
#
#
#Learn Media Window for Reference Media
#
#Ask the user if they want to replace the media with
#new media or with a reference tag's media.
If [ Left ( Get ( LayoutName ) ; 8 ) = "LearnRef" ]
Set Variable [ $referenceLayout; Value:1 ]
Show Custom Dialog [ Message: "Add a new picture or movie or display a different reference tag's picture or movie?"; Default
Button: “cancel”, Commit: “Yes”; Button 2: “display”, Commit: “No”; Button 3: “new”, Commit: “No” ]
#
#If the user cancels, exit this script.
If [ Get (LastMessageChoice) = 1 ]
Exit Script [ ]
#
#If the user decides on using a reference tag's media,
#tell the user how to do this.
Else If [ Get (LastMessageChoice) = 2 ]
If [ $$pictureWindowColor = "test" or $$pictureWindowColor = "report" ]
#If on a test module layout...
Show Custom Dialog [ Message: "1) Click 'back'. 2) Click 'edit/new'. 3) Click 'Qv'. 4) From the Qv's reference section,
select a reference tag's picture/movie to show."; Default Button: “OK”, Commit: “Yes” ]
Else
#If on a Learn module layout...
Show Custom Dialog [ Message: "1) click 'back'. 2) Click 'Qv'. 3) From the Qv's reference section, select a reference
tag's picture/movie to show."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#If the user decides on new media, add new media.
Else If [ Get (LastMessageChoice) = 3 ]
Set Variable [ $refMediaLayout; Value:Get (LayoutName) ]
Set Variable [ $kshowReferencedMedia; Value:testlearn::kshowReferencedMedia ]
#
#Go to Learn media layout to accept
#new learn media.
Go to Layout [ “LearnPictureWindowEDIT” (testlearn) ]
Perform Script [ “CHUNK_insertPictureOrMovie” ]
If [ testlearn::picture = "" ]
Go to Layout [ $refMediaLayout ]
Set Field [ testlearn::kshowReferencedMedia; $kshowReferencedMedia ]
End If
End If
#
#
#
#
#Reference Media Window
Else If [ Left ( Get ( LayoutName ) ; 9 ) = "reference" and Get ( LayoutTableName ) = "reference" ]
#
#
#Ask the user if they want to replace media
#with new media or display web or HDD
#media, UNLESS the library is in inventory
#mode, in which case the only option is to
#replace the media in the picture field, so
#don't ask any questions, just proceed to
#replacing it.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Perform Script [ “CHUNK_insertPictureOrMovie” ]
#
Else If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Add a new picture or movie, or display web or harddrive media?"; Default Button:
“cancel”, Commit: “Yes”; Button 2: “display”, Commit: “No”; Button 3: “new”, Commit: “No” ]
#
#If the user cancels, exit this script.
If [ Get (LastMessageChoice) = 1 ]
Exit Script [ ]
#
#If the user decides on displaying external media,
#tell the user how to do this.
Else If [ Get (LastMessageChoice) = 2 ]
#
#
If [ $$replacePicture = 1 ]
Set Variable [ $$replacePicture ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
Close Window [ Name: "Media"; Current file ]
#
Else If [ $$replacePicture = "" ]
#
If [ reference::showMedia[1] = "" and reference::showMedia[2] = "" ]
Show Custom Dialog [ Message: "1) Click 'x' to delete the current picture. 2) Click 'back'. 3) Add a webpage
url below and click the WebMedia checkbox, or 4) enter a media file's name, add its folder-path tag, and
click the HDDMedia checkbox."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "1) Click 'back'. 3) Add a new webpage url below and click the WebMedia
checkbox, or 4) enter a new media file's name, add its folder-path tag, and click the HDDMedia
checkbox."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#If the user decides on new media = message
#choice 3, replace the media.
Else If [ Get (LastMessageChoice) = 3 ]
#
#The replace button could have been clicked
#on a web or HDD media layout, so go to the
#picture field layout before adding media to it.
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
#
#Add new media.
Perform Script [ “CHUNK_insertPictureOrMovie” ]
#
#If user canceled add and there is no picture
#return to the layout on which the replace was
#button was clicked.
If [ reference::picture = "" ]
Go to Layout [ original layout ]
#
#If the user added new media, make sure web
#and harddrive checkboxes are unchecked.
Else
Set Field [ reference::showMedia; "" ]
Set Field [ reference::showMedia[2]; "" ]
End If
End If
#
End If
#
#
#
#
#Learn Media Window
Else
#
#Ask the user if they want to replace the media with
#new media or with a reference tag's media, except
#when on the test layout where users can only add
#new media.
If [ testlearn::filterFind = "main" & ¶
or
testlearn::filterFind = "main" ]
#If on a Learn module layout...
Show Custom Dialog [ Message: "Add a new picture or movie or display a reference tag's picture or movie?"; Default
Button: “cancel”, Commit: “Yes”; Button 2: “display”, Commit: “No”; Button 3: “new”, Commit: “No” ]
Else If [ testlearn::filterFind = "" ]
#If on a test module layout...
Show Custom Dialog [ Message: "Add a new picture or movie?"; Default Button: “cancel”, Commit: “Yes”; Button 3: “new”,
Commit: “No” ]
End If
#
#If the user cancels, exit this script.
If [ Get (LastMessageChoice) = 1 ]
Exit Script [ ]
#
#If the user decides on using a reference tag's media,
#tell the user how to do this.
Else If [ Get (LastMessageChoice) = 2 ]
If [ $$pictureWindowColor = "test" or $$pictureWindowColor = "report" ]
#If on a test module layout...
Show Custom Dialog [ Message: "1) Click 'x' to delete the current picture. 2) Click 'back'. 3) Click 'edit/new'. 4) Click
'Qv'. 5) From the Qv's reference section, select a reference tag's picture/movie to show."; Default Button: “OK”,
Commit: “Yes” ]
Else
#If on a Learn module layout...
Show Custom Dialog [ Message: "1) Click 'x' to delete the current picture. 2) Click 'back'. 3) Click 'Qv'. 4) From the
Qv's reference section, select a reference tag's picture/movie to show."; Default Button: “OK”, Commit: “Yes” ]
End If
#
Else If [ Get (LastMessageChoice) = 3 ]
#If the user decides on new media, add new media.
Perform Script [ “CHUNK_insertPictureOrMovie” ]
End If
End If
#
