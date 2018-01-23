January 17, 2018 23:20:18 Library.fmp12 - newReference -1-
reference: newReference
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Cancel find mode, then click this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
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
Sort Records [ ]
[ No dialog ]
#
#Copy primary key word/subject of current
#record so it can be given to then new record.
# The user will expect that clicking the 'new'
#button will result in new record in the current
#subject area.
Set Variable [ $P; Value:reference::kkeywordPrimary ]
#
Go to Field [ ]
#
#Now create a new record and give it the
#copied subject/keyword.
Set Variable [ $$stoploadCitation; Value:1 ]
New Record/Request
Set Field [ reference::kkeywordPrimary; $P ]
#
#Load new record as the record being
#focused on.
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord” ]
#
#Determine if in stuff or idea mode.
If [ TEMP::InventoryLibraryYN ≠ "" ]
#
#If in stuff mode than select to
#show record in the Learn section.
Set Field [ reference::showInLearn; "show in learn" ]
#
#Decided to make main reference layout also
#include the fields that will be edited, so no
#need in stuffLibrary mode to go an
#edit layout.
Else
#
#If in idea mode then open new record in a
#separate window. This is neccessary to allow
#user to scroll thru just this new record after
#finding just this new record in the new
#window.
# Also, the new window strategy means the
#main reference window will not need to be
#resorted, and so moved unless the
#alphabetical location of this new record
#requires it to be resorted.
Set Variable [ $$stoploadCitation; Value:1 ]
Sort Records [ ]
[ No dialog ]
Set Variable [ $$editRecord; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $$editRecord ]
[ No dialog ]
#
#Go to edit layout in new window.
Set Window Title [ Current Window; New Title: "Hidden" ]
#
#Mark record as incomplete.
Set Field [ reference::incomplete; "incomplete" & ¶ ]
#
#For some reason it is essential that a Go to
#field step is included prior to opening the
#new window for Add to tags scripts to work.
Go to Field [ ]
#
New Window [ Name: "References"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
Go to Layout [ “ReferenceEDIT” (reference) ]
#
#Find just the record to be edited.
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $$citationRecord ]
Perform Find [ ]
Set Variable [ $$stoploadCitation ]
#
End If
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
#
