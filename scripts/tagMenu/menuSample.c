January 15, 2018 16:30:38 Library.fmp12 - menuBrainstorm -1-
tagMenu: menuBrainstorm
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#Prevent halting of script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#If user was viewing test tags then do this.
If [ $$citationMatch = "test" ]
#
#Go to Learn window.
Select Window [ Name: "Learn"; Current file ]
#
#Clear brainstorm and test tags.
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
#
#Return to Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#Clear order numbers.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Height: 1; Width: 1; Top: -100000; Left: -100000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “learnSCRIPTloops” (testlearn) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testlearn::orderTestInformation: “###” ]
[ Restore ]
Loop
Set Field [ testlearn::orderTestInformation; "" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Close Window [ Current Window ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$doNotHaltOtherScripts ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"brainstorm" ]
#
#Set match temp tag field to limit move pulldown
#to just the groups for this section and item type.
#( if you're wondering why this temp field is a
# a dupllicate of the citation match variable it
# is because I didn't need it until a year into
# writing this database. At some point, it would
# probably be good to get rid of the variable. )
Set Field [ TEMP::mTag; $$citationMatch ]
#
#Turn off the loadtagrecord script to speed up the
#loop portion of the script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadCitation; Value:1 ]
#
#Goto correct layout.
Go to Layout [ “learnMenuBrainstorm” (tagMenus) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnMenuStuffBrainstorm” (tagMenus) ]
End If
#
#Find brainstorm tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Sort into groups.
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list: “order
Pulldown List”
tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $number; Value:1 ]
Go to Field [ ]
Loop
Exit Loop If [ Middle ( GetValue ( $$brainstorm ; $number ) ; 4 ; 42 ) & "¶" = tagMenus::_Ltag & ¶ ]
Exit Loop If [ Middle ( GetValue ( $$brainstorm ; $number ) ; 4 ; 42 ) = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Exit Loop If [ Middle ( GetValue ( $$brainstorm ; $number ) ; 4 ; 42 ) & "¶" = tagMenus::_Ltag & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn loadtagrecord script back on.
Set Variable [ $$stopLoadTagRecord ]
#
#Turn loadtagrecord script back on and perform
#loadtag... script to highlight any Learn records
#tagged with the current tag record.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadBrainstormTags (update name change loadItemRecordForSampleTagMenu)” ]
#
