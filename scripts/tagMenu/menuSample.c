tagMenu: menuSample
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Clear sample and test tags.
If [ $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagSample ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#Clear order numbers.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Height: 1; Width: 1 ]
Go to Layout [ “learnSCRIPTloops” (testlearn) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testlearn::orderTest: “###” ]
[ Restore ]
Loop
Set Field [ testlearn::orderTest; "" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Close Window [ Current Window ]
Set Variable [ $$stopLoadTagRecord ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"sample" ]
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
Go to Layout [ “learnMenuSample” (tagMenus) ]
#
#Find sample tags for current library section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortSample = "cat" or TEMP::sortSample = "" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortSample = "abc" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $number; Value:1 ]
Go to Field [ ]
Loop
Exit Loop If [ Middle ( GetValue ( $$sample ; $number ) ; 4 ; 42 ) & "¶" = tagMenus::_Ltag & ¶ ]
Exit Loop If [ Middle ( GetValue ( $$sample ; $number ) ; 4 ; 42 ) = "" ]
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Exit Loop If [ Middle ( GetValue ( $$sample ; $number ) ; 4 ; 42 ) & "¶" = tagMenus::_Ltag & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn loadtagrecord script back on.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “insureEqualityOfSpellFields” ]
#
#Turn loadtagrecord script back on and perform
#loadtag... script to highlight any Learn records
#tagged with the current tag record.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadItemRecordForSampleTagMenu” ]
#
#
#
// If [ Middle ( GetValue ( $$sample ; $number ) ; 4 ; 42 ) & "¶" ≠ tagMenus::_Ltag & ¶ ]
// Go to Record/Request/Page
[ First ]
// Select Window [ Name: "Learn"; Current file ]
// #
// #If sort by order number is on then sort by
// #order number.
// If [ TEMP::TLSampleSort = 1 ]
// Set Field [ TEMP::TLSampleSort; "" ]
// Perform Script [ “SortTLRecordsByOrderNumber” ]
// Else If [ TEMP::TLSampleSort = "" ]
// Set Field [ TEMP::TLSampleSort; 1 ]
// Perform Script [ “SortTLRecordsByOrderNumber” ]
// End If
// Go to Field [ ]
// Refresh Window
// Select Window [ Name: "Tag Menus"; Current file ]
January 7, 平成26 16:00:02 Imagination Quality Management.fp7 - menuSample -1-tagMenu: menuSample
// Exit Script [ ]
// End If
// #
// #Inform user of items use on both screens.
// Set Variable [ $$citationItem; Value:tagMenus::_Ltag ]
// Set Variable [ $$tagSample; Value:tagMenus::_Ltag ]
// Set Variable [ $$sampleORTestID; Value:Get (RecordID) ]
// Refresh Window
// #
// #Just in case user was in nonTag field on this
// #window when user clicked a menu button on
// #the other window, exit all fields.
// Set Variable [ $$stopLoadCitation ]
// Select Window [ Name: "Learn"; Current file ]
// #
// #If sort by order number is on then sort by
// #order number.
// If [ TEMP::TLSampleSort = 1 ]
// Set Field [ TEMP::TLSampleSort; "" ]
// Perform Script [ “SortTLRecordsByOrderNumber” ]
// Else If [ TEMP::TLSampleSort = "" ]
// Set Field [ TEMP::TLSampleSort; 1 ]
// Perform Script [ “SortTLRecordsByOrderNumber” ]
// End If
// Go to Field [ ]
// Refresh Window
// Select Window [ Name: "Tag Menus"; Current file ]
January 7, 平成26 16:00:02 Imagination Quality Management.fp7 - menuSample -2-
