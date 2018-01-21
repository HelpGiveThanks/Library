January 15, 2018 14:55:59 Library.fmp12 - testItemCheckOrTextOrForm -1-
test: test: testItemCheckOrTextOrForm
#
#On the test-item layout, set this stop check
#or text variable to allows the user to click into
#this field for the purpose of navigating to a
#new record without changing the check or
#text mark status.
If [ $$stopCheckOrTest = 1 ]
Set Variable [ $$stopCheckOrTest ]
Exit Script [ ]
End If
#
#Prevent user from changing check/text
#status of locked records.
If [ tagCreatorLock::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & tagCreatorLock::tag & " — in the
setup tag window and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#Prevent the test check items from being
#turned into T or FT items if they are
#in use as check items.
If [ tagMenus::notesOrCopyright = "✓" ]
#Get variables needed for delete and delete messages.
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Set Variable [ $group; Value:tagMenuTestItemGroup::_Lgroup ]
Set Variable [ $groupName; Value:If ( Char ( tagMenuTestItemGroup::name ) ≤ 20 ; tagMenuTestItemGroup::name ; Left
( tagMenuTestItemGroup::name ; 20 ) & "..." ) ]
Set Variable [ $testItemName; Value:If ( Char ( tagMenus::tag ) ≤ 20 ; tagMenus::tag ; Left ( tagMenus::tag ; 20 ) & "..." ) ]
#
#
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopDeleteTest; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
New Window [ Name: " "; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
Go to Layout [ “tableTestLearn” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::kctestResultCheckedItems; $delete ]
Perform Find [ ]
#
#If this section is found to be in use, then inform
#user of where and prevent its deletion.
If [ Get (LastError) ≠ 401 ]
Loop
Set Variable [ $useList; Value:TextColor(
tagTLTestSubject::tag &
" | test " &
testlearn::kreportNumber &
¶ &
"section "
 ;RGB(102;102;102))
& testSectionTemplateName::name &
¶ &
TextColor(
"sub-section "
 ;RGB(102;102;102))
& testlearn::subsectionCustomName ]
Go to Layout [ “TEMP” (TEMP) ]
New Record/Request
Set Field [ TEMP::DeleteMessageInTempWindow1; $useList ]
Go to Layout [ “testResult0” (testlearn) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ “TEMP” (TEMP) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::DeleteMessageInTempWindow1; ascending ]
[ Restore; No dialog ]
View As
[ View as List ]
#
Show/Hide Toolbars
[ Lock; Hide ]
Show/Hide Text Ruler
[ Hide ]
#
#Due to a bug in FM13, window must first be
#moved back into the screen area before the
#calculation of the current screen's
#dimensions can be taken.
Move/Resize Window [ Current Window; Top: 0; Left: 0 ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 360; Top: 0; Left: Get ( ScreenWidth ) - ( Get
( ScreenWidth )/2 + 360) ]
Set Field [ TEMP::Message; "Before the highlighted test item can be turned into a T or FT item, it must unchecked " & "(in the
test module) from test results in the test sub-sections below." ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
Set Variable [ $delete ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Refresh Window
Exit Script [ ]
Else
Close Window [ Current Window ]
Set Variable [ $delete ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Refresh Window
End If
End If
#
#
#Change this test item's check or text mark
#status. This status determines if and when
#the test item's button is clicked a check is put
#next to it or its text is copied and pasted into
#a test results text field.
Set Field [ tagMenus::notesOrCopyright; Case ( tagMenus::match = "testItem" ;
 Case ( tagMenus::notesOrCopyright = "" ; "✓" ;
 Case ( tagMenus::notesOrCopyright = "✓" ; "T" ;
 Case ( tagMenus::notesOrCopyright = "T" ; "FT" ;
 Case ( tagMenus::notesOrCopyright = "FT" ; "✓" ) ) ) ) ) ]
Commit Records/Requests
If [ tagMenus::notesOrCopyright = "✓" ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; "" ]
Set Field [ tagMenus::tag; Trim (tagMenus::tag) ]
Set Field [ tagMenus::tag; TextFontRemove ( tagMenus::tag ) ]
Set Field [ tagMenus::tag; TextSizeRemove ( tagMenus::tag ; 20 ) ]
Set Field [ tagMenus::tag; TextStyleRemove ( tagMenus::tag ; Bold ) ]
Set Field [ tagMenus::tag; TextColorRemove ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
#
#Now force FileMaker to update formatting in
#the tagSpelling field, which is what shows the
#tag when the checkmark symbol is used.
Set Field [ tagMenus::tagSpelling; tagMenus::tag ]
End If
Refresh Window
#
#
