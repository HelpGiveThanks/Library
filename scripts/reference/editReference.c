January 18, 2018 14:37:28 Library.fmp12 - editReference -1-
reference: editReference
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
#If node is currenlty locked then stop script, inform user.
If [ refCreatorNode::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record was created by " & $$lockedMainRefRecord & ", a node which is locked. Select
this node in the setup window and enter the password to unlock it. You can edit your location for this locked reference's file.";
Default Button: “OK”, Commit: “Yes” ]
End If
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Cancel find mode, then click this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If file name is for media that is being used to
#show a picture set variable to insure media is
#not deleted if in use as determined by this
#script exitAndSeeIfMediaIsInUse.
If [ reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "jpg"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "gif"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "psd"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "png"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tga"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tif"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "bmp" ]
Set Variable [ $$fileNameFieldHasMedia; Value:1 ]
End If
#
#If in find mode, exit find mode.
If [ $$findMode= 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Go to Layout [ $$findLayout ]
Set Variable [ $$stoploadCitation ]
Select Window [ Name: "References"; Current file ]
End If
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
Select Window [ Name: "References"; Current file ]
#
#Go to edit layout in new window.
Set Window Title [ Current Window; New Title: "Hidden" ]
#
#For some reason it is essential that a Go to
#field step is included prior to opening the
#new window for Add to tags scripts to work.
Go to Field [ ]
#
#Open new window and title it references
#as the add tag scripts look for the
#references window.
New Window [ Name: "References"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
If [ refCreatorNode::orderOrLock ≠ "" ]
Go to Layout [ “ReferenceFilePathEDIT” (reference) ]
Else
Go to Layout [ “ReferenceEDIT” (reference) ]
End If
#
#Get rid of spaces in bookChapter field, if any.
Set Field [ reference::bookChapter; Trim ( reference::bookChapter ) ]
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
#
#Note records position so on the way back
#from the edit window the system can
#determine if it moved as a result of editing it.
Set Variable [ $$editRecord; Value:Get (RecordNumber) ]
#
#Find just the record to be edited.
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $$citationRecord ]
Perform Find [ ]
#
