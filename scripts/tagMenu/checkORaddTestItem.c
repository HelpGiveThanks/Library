January 15, 2018 16:58:39 Library.fmp12 - checkORaddTestItem -1-
tagMenu: checkORaddTestItem
#
#
#
#If check button was clicked and this is a text
#item, then go to the text field.
If [ $$checkButton ≠ "" and tagMenus::notesOrCopyright = "T"
 or
$$checkButton ≠ "" and tagMenus::notesOrCopyright = "FT" ]
Set Variable [ $$checkButton ]
Go to Field [ tagMenus::tagLocked ]
Exit Script [ ]
Else
Set Variable [ $$checkButton ]
End If
#
#
#
#If text button was clicked and this is a check
#item, then go to the text field.
If [ $$textButton ≠ "" and tagMenus::notesOrCopyright ≠ "T" and tagMenus::notesOrCopyright ≠ "FT" ]
Set Variable [ $$textButton ]
Go to Field [ tagMenus::tagLocked ]
Exit Script [ ]
Else
Set Variable [ $$textButton ]
End If
#
#
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
#
#
#Stop this script if any of the following are true:
#
#Test subject is locked.
If [ $$testSubjectIsLocked ≠ "" and Get ( LayoutName ) ≠ "defaultTest" and Get ( LayoutName ) ≠ "learnTest" ]
Show Custom Dialog [ Message: "The test subject — " & $$testSubjectIsLocked & " — is locked. To unlock, A) go back to the
setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button: “OK”, Commit:
“No” ]
Set Variable [ $exit; Value:1 ]
End If
#
#Primary node is locked.
If [ TEMP::primaryNodeIsLocked ≠ "" ]
If [ $exit = "" ]
Show Custom Dialog [ Message: "The default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked.
Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary node, or C)
create a new primary node."; Default Button: “OK”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "ALSO, the default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is
locked. Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary
node, or C) create a new primary node."; Default Button: “OK”, Commit: “No” ]
End If
Set Variable [ $exit; Value:1 ]
End If
#
#If any of the above are true, then
#exit this script.
If [ $exit = 1 ]
Exit Script [ ]
End If
#
#
#
#Admin tags.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Go to Field [ ]
#
#
#
#
#
#BEGIN Text Item
#
#
#
#
#
#If a text T item is selected then the user wants to
#add the text of the test item to the note field.
#
#Add text T item to the selected field
#or note field.
If [ tagMenus::notesOrCopyright = "T" or tagMenus::notesOrCopyright = "FT" or Left (Get ( LayoutName ) ; 6 ) = "report" ]
#
#
#Format text to be inserted.
#
#IMPORTANT: Leave the order of the variables
#abelow as is! Changes to the order result in
#formatting failures!!!
If [ tagMenus::textStyleOrCreatorNodeFlag = ""
or
tagMenus::textStyleOrCreatorNodeFlag ≠ 1 and tagMenus::textStyleOrCreatorNodeFlag ≠ 2 and tagMenus::
textStyleOrCreatorNodeFlag ≠ 3 ]
Set Variable [ $tag; Value:TextFont ( tagMenus::tag ; "Georgia" ) ]
Set Variable [ $tag; Value:TextColor ( $tag ; RGB ( 34 ; 34 ; 34 ) ) ]
Set Variable [ $tag; Value:TextSize ( $tag ; 16 ) ]
Set Variable [ $tag; Value:TextStyleAdd ( $tag ; Plain ) ]
Else If [ tagMenus::textStyleOrCreatorNodeFlag = "1" ]
Set Variable [ $tag; Value:TextFont ( tagMenus::tag ; "Georgia" ) ]
Set Field [ tagMenus::tag; TextColor ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
Set Variable [ $tag; Value:TextSize ( $tag ; 16 ) ]
Set Variable [ $tag; Value:TextStyleAdd ( $tag ; Plain ) ]
Else If [ tagMenus::textStyleOrCreatorNodeFlag = "2" ]
Set Variable [ $tag; Value:TextFont ( tagMenus::tag ; "Arial" ) ]
Set Variable [ $tag; Value:TextColor ( $tag ; RGB ( 34 ; 34 ; 34 ) ) ]
Set Variable [ $tag; Value:TextSize ( $tag ; 16 ) ]
Set Variable [ $tag; Value:TextStyleAdd ( $tag ; Plain ) ]
Else If [ tagMenus::textStyleOrCreatorNodeFlag = "3" ]
Set Variable [ $tag; Value:TextFont ( tagMenus::tag ; "Arial" ) ]
Set Field [ tagMenus::tag; TextColor ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
Set Variable [ $tag; Value:TextSize ( $tag ; 20 ) ]
Set Variable [ $tag; Value:TextStyleAdd ( $tag ; Bold ) ]
End If
#
#Create a clear formatting variable to insure
#anything typed after the newly inserted text
#will be in the default format.
Set Variable [ $clearFormatting; Value:TextFont ( " " ; "Georgia" ) ]
Set Variable [ $clearFormatting; Value:TextColor ( $clearFormatting ; RGB ( 34 ; 34 ; 34 ) ) ]
Set Variable [ $clearFormatting; Value:TextSize ( $clearFormatting ; 16 ) ]
Set Variable [ $clearFormatting; Value:TextStyleAdd ( $clearFormatting ; Plain ) ]
#
#
#See if the user in the test section
#or report section of the library.
Select Window [ Name: "Test"; Current file ]
If [ Get ( LastError )= 112 ]
Select Window [ Name: "Report"; Current file ]
Set Variable [ $note; Value:report::note ]
Else
Set Variable [ $note; Value:testlearn::note ]
End If
#
#If the user is not in a field, then add the text
#to the note field.
If [ Get ( ActiveFieldName ) = "" ]
#
#If there is nothing in the field, then enter
#the new text at the top of the field.
If [ $note = "" ]
#There is a bug in FMGO16 where the format of
#the first character defines the format for the
#textbox. The only way around this is to put in
#several blank lines between to default
#formatted spaces, and then enter new text on
#one of these lines.
Set Field [ testlearn::note; $tag & $clearFormatting & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & $clearFormatting ]
Set Field [ report::note; $tag & $clearFormatting & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & $clearFormatting ]
#
#
Else
#If there is text in the field, it is possible any
#new text will be inserted out of sight, unless
#the field is entered and then scrolled to
#the bottom.
#
#SO, first enter the field and insert the current
#contents to activate it, which will then allow for
#the insert command, next.
If [ Get (LayoutTableName) = "testlearn" ]
Go to Field [ testlearn::note ]
Set Field [ testlearn::note; $note & $clearFormatting ]
Else
Go to Field [ report::note ]
Set Field [ report::note; $note & $clearFormatting ]
End If
#
#Insert the new T item, and the field will
#scroll to the bottom and insert the item
#allowing the user to see the insert.
Insert Calculated Result [ ¶ & $tag & $clearFormatting & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ &
$clearFormatting ]
End If
#
#
#If the field is active then insert the text block.
Else If [ Get ( ActiveFieldName ) ≠ "" ]
If [ Get ( ActiveFieldContents ) = "" ]
#There is a bug in FMGO16 where the format of
#the first character defines the format for the
#textbox. The only way around this is to put in
#several blank lines between to default
#formatted spaces, and then enter new text on
#one of these lines.
Set Field [ testlearn::note; $tag & $clearFormatting & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & $clearFormatting ]
Else
Insert Calculated Result [ $tag & $clearFormatting ]
End If
End If
#
#
Exit Script [ ]
End If
#
#
#
#
#
#END Text Item
#
#
#
#
#
#BEGIN Check Item
#
#
#
#
#
#If check is selected then the user wants
#this tag's key added or removed from
#the test result.
#
#Get key for tag that is to be added or removed.
Set Variable [ $tag; Value:tagMenus::_Ltag ]
#
#Go the Test window.
Select Window [ Name: "Test"; Current file ]
#
#First, see if the test item has already
#been added.
#
#Set the number variable to 1, so the loop
#below will check the first key in the test
#result's test-item keychain, and the proceed to
#check all the rest for the currently selecte item.
Set Variable [ $number; Value:1 ]
Loop
#
#If the item's tag is found in this keychain,
#then remove it.
If [ FilterValues ( GetValue ( testlearn::kctestResultCheckedItems ; $number ) ; $tag & "¶" ) = $tag & ¶ ]
Set Field [ testlearn::kctestResultCheckedItems; Substitute ( $$checkedTestItem ; GetValue ( testlearn::
kctestResultCheckedItems ; $number ) & "¶" ; "" ) ]
#
#Reset this result's test-item keychain variable.
Set Variable [ $$checkedTestItem; Value:testlearn::kctestResultCheckedItems ]
#
#Set the number variable to 'found' which
#will stop this loop.
Set Variable [ $number; Value:"found" ]
End If
#
#If number variable was set to exit or if no keys
#exist, then exit this loop.
Exit Loop If [ GetValue ( testlearn::kctestResultCheckedItems ; $number ) = ""
 or
$number = "found" ]
#
#If variable looked at did not match the selected
#item's key then raise the number variable by 1
#to look at the next item key in this result's
#keychain.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
#
#
#If this item's key was not found in the
#keychain-loop check above, then proceed
#to add it to this result's test-item keychain.
If [ $number ≠ "found" ]
Set Field [ testlearn::kctestResultCheckedItems; $tag & ¶ & $$checkedTestItem ]
#
#Reset this result's test-item keychain variable.
Set Variable [ $$checkedTestItem; Value:testlearn::kctestResultCheckedItems ]
End If
#
#
#Return to the Tag Menus window and
#update the conditional formatting
#of the now unchecked
#or checked item.
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Go to Field [ ]
#
#
#END Check item
#
#
