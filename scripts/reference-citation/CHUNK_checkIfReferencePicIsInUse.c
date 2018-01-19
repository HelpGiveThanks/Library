January 18, 2018 14:48:57 Library.fmp12 - CHUNK_checkIfReferencePicIsInUse -1-
reference: CHUNK_checkIfReferencePicIsInUse
#
#
#NOTE: this code is copied from the script
#deleteReference.
# SO if there is a problem with this code
#check to make sure it is also addressed
#in that script too.
#
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Set Variable [ $windowName; Value:Get (WindowName) ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
#
#
#Insure when script is done and the picture
#window is closed the user sees the
#References window and not the Tag Menus
#window.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: $windowName; Current file ]
#
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
#
#
#Set variables to find other records using
#its media.
Set Variable [ $delete; Value:reference::_Lreference ]
Set Variable [ $deleteName; Value:reference::_Number ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#
#Because there may be no records found, stop
#the system from informing the user of this.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#Open a new window and look for record's
#media being used by another record.
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#
#See if reference's media is used
#by any learn records, which in turn might be
#used on a report, which is something that
#would be nice to know and finding out
#should be added at later date.
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kshowReferencedMedia; $delete ]
Perform Find [ ]
#
If [ Get (LastError) ≠ 401 ]
Set Variable [ $inUse; Value:Get (FoundCount) & " Learn" ]
End If
#
#
#See if reference record's media
#is used by any tag records.
#There are three pictures per record.
Go to Layout [ “tableTag” (tagTable) ]
#
#picture1
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture1; $delete ]
Perform Find [ ]
Set Variable [ $tagFound1; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#picture2
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture2; $delete ]
Perform Find [ ]
Set Variable [ $tagFound2; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#picture3
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture3; $delete ]
Perform Find [ ]
Set Variable [ $tagFound3; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
If [ $tagFound1 + $tagFound2 + $tagFound3 ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & ", " & ($tagFound1 + $tagFound2 + $tagFound3) & " Tag Menus (picture for
tag: " & $tagName & ")" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " Tag Menus (picture for tag: " & $tagName & ")" ]
End If
End If
#
#
#Close window used to find records that
#might be using the reference's media.
Close Window [ Current Window ]
#
#
#Report on findings if there are any.
If [ $inUse ≠ "" ]
Set Variable [ $delete ]
Refresh Window
#
#
#If this script was run by the either the
#web or hdd media check box scripts...
If [ $$showRefURLmedia ≠ "" ]
#
#Re-check the unchecked checkbox.
If [ $$showRefURLmedia = 1 ]
Set Field [ reference::showMedia; 1 ]
Else
Set Field [ reference::showMedia[2]; 2 ]
End If
#
#Inform user this reference's media is in use and must
#be replaced or left as is (thus the re-checking of the
#media check box).
Show Custom Dialog [ Message: "MEDIA REQUIRED (picture, etc.) in use by X number of records here: " & $inUse & ".";
Default Button: “cancel”, Commit: “Yes”; Button 2: “replace”, Commit: “No” ]
#
#If user cancels, then exit this script and
#the picture delete script.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $$pictureDelete; Value:2 ]
#
#Turn off variables that where turned on
#by this script to speed it up.
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
#If the user decides to replace the media, then put a
#place holder in the picture field until the user replaces
#it. This way, if the user leaves the reference record
#without replacing in-use media, at least this
#place holder will show up where this reference's
#media is in use.
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::showMedia; "" ]
Set Field [ reference::showMedia[2]; "" ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
End If
#
#
#If this script was run by the pictureDelete script...
Else If [ $$pictureDelete = 1 ]
#
#Inform user this reference's media is in use and must
#be replaced or left as is.
Show Custom Dialog [ Message: "MEDIA REQUIRED (picture, etc.) in use by X number of records here: " & $inUse & ".";
Default Button: “cancel”, Commit: “Yes”; Button 2: “replace”, Commit: “No” ]
#
#If user cancels, then exit this script and
#the picture delete script.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $$pictureDelete; Value:2 ]
#
#Turn off variables that where turned on
#by this script to speed it up.
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
#If user clicks replace, then run script
#to replace it and exit the delete script.
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $$pictureDelete; Value:2 ]
Set Variable [ $$replacePicture; Value:1 ]
#
#Turn off variables that where turned on
#by this script to speed it up.
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
End If
#
End If
#
