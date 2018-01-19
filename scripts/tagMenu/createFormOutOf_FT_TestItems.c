January 15, 2018 17:04:22 Library.fmp12 - createFormOutOf_FT_TestItems -1-
tagMenu: createFormOutOf_FT_TestItems
#
#
#Exit any fields before beginnning just in
#case the user changed the spelling of
#anything that would require the spellcheck
#script to run.
Go to Field [ ]
#
#
#
#
#
#BEGIN Stop this script checks.
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
#END Stop this script checks.
#
#
#
#
#
#BEGIN See where to insert form.
#
#
#If the user clicks the V button on the setup
#test-item layout, skip this bit, otherwise see
#where the user wants to put the form this
#script will create on a Test or Report field.
If [ Left (Get (LayoutName) ; 5 ) ≠ "setup" ]
#
#Select the test window and copy the contents
#of the note field and see if it is active.
Select Window [ Name: "Test"; Current file ]
#
#If library is in the report section ...
If [ Get ( LastError )= 112 ]
Select Window [ Name: "Report"; Current file ]
Set Variable [ $report; Value:1 ]
#
#If the user has not clicked into a field, into
#which to insert the form let them know they
#need to do this before the form can be inserted.
If [ Get ( ActiveFieldName ) = "" ]
Show Custom Dialog [ Message: "Enter the field where you want the form to go. It will be placed below any text
currently in that field."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
#
#
Else
#If a field has been selected then capture
#its contents if any.
Set Variable [ $note; Value:Get ( ActiveFieldContents ) ]
End If
#
#
#If library is in the learn section ...
Else
#
#Capture the contents of the active field.
Set Variable [ $note; Value:testlearn::note ]
End If
#
#Return to the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
#
#If the note field is not blank ...
If [ $note ≠ "" ]
#
#Tell the user that a form will be added below
#the current text in the note text box, AND if
#the user hiding the test FT items that make up
#a form, tell the user how to reveal them.
If [ TEMP::testHideFormTextItemsFTs = 1 ]
Show Custom Dialog [ Message: "A form will be added below the current text. You may need to scroll down to see it.
To view test items used to make this form, click the 'hideFTs' button."; Default Button: “OK”, Commit: “Yes”; Button
2: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "A form will be added below the current text. You may need to scroll down to see it.";
Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
End If
End If
#
#
#If the user is on the setup layout, note this.
Else If [ Left (Get (LayoutName) ; 5 ) = "setup" ]
Set Variable [ $insertFormInPreviewWindow; Value:1 ]
End If
#
#
#END See where to insert form.
#
#
#
#
#
#BEGIN Create form.
#
#
#Create the form, unless the user
#clicked cancel in a new window.
If [ Get (LastMessageChoice) ≠ 2 ]
Set Variable [ $$userClickedVButton; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
New Window [ Name: "Form Preview"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area:
“Yes”; Resize: “Yes” ]
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
Adjust Window
[ Resize to Fit ]
#
Set Variable [ $$userClickedVButton ]
Set Variable [ $$stopLoadTagRecord ]
#
#Find all test items for this subsection.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenuTestItemGroup::match; TEMP::ktestItemSubsection & ¶ ]
Set Field [ tagMenus::copyrightTextLockedORtextTitem; "FT" ]
Perform Find [ ]
#
#To insure the 'sort' button will next sort
#alphabetically, note that the current sort is
#by category/group.
Set Field [ TEMP::sortTestItem; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on value
list: “order Pulldown List”
tagMenuTestItemGroup::name; ascending
tagMenuTestItemGroup::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
#
#Now, get all FT text items = build the form.
Go to Record/Request/Page
[ First ]
Loop
#
#Stop any find error messages as there may be
#no test items.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
Go to Field [ ]
#
#If the item is an FT item then add it to the
#form.
If [ tagMenus::notesOrCopyright = "FT" ]
#
#If the style of the FT item is main header style ...
If [ tagMenus::textStyleOrCreatorNodeFlag = ""
 or
tagMenus::textStyleOrCreatorNodeFlag = "1"
 or
tagMenus::textStyleOrCreatorNodeFlag = "2" ]
Set Variable [ $tag; Value:tagMenus::tag ]
Else
#
#and it is not the first form item ...
If [ $tag = "" ]
Set Variable [ $tag; Value:tagMenus::tag ]
#
#then include a paragraph between it and
#the last FT item added.
Else
Set Variable [ $tag; Value:¶ & tagMenus::tag ]
End If
End If
#
#If this the first item on this form,
#then just added it.
If [ $form = "" ]
Set Variable [ $form; Value:$tag ]
#
#BUT, if the form already has items in it, then
#add this next item a paragraph below the last
#item in the form.
Else
Set Variable [ $form; Value:$form & ¶ & $tag ]
End If
End If
#
Go to Record/Request/Page
[ Next; Exit after last ]
#
End Loop
End If
#
#
#END Create form.
#
#
#
#
#
#
#BEGIN Insert form in designated field.
#
#
#If it turns out there are no FT items, then tell
#the user this and exit the script.
If [ $form = "" ]
Close Window [ Current Window ]
Show Custom Dialog [ Message: "There are no form test (FT) items."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#Create a clear formatting variable to insure
#anything typed after the newly inserted form
#will be in the default format.
Set Variable [ $clearFormatting; Value:TextFont ( " " ; "Georgia" ) ]
Set Variable [ $clearFormatting; Value:TextColor ( $clearFormatting ; RGB ( 34 ; 34 ; 34 ) ) ]
Set Variable [ $clearFormatting; Value:TextSize ( $clearFormatting ; 16 ) ]
Set Variable [ $clearFormatting; Value:TextStyleAdd ( $clearFormatting ; Plain ) ]
#
#
#If the user is in the Test Template section,
#then go to the preview form layout and
#insert the form.
If [ $insertFormInPreviewWindow ≠ "" ]
Go to Layout [ “testItemFormPreview” (TEMP) ]
Set Field [ TEMP::Message; $form ]
Adjust Window
[ Resize to Fit ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight) ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
End If
#
#If the user is NOT in the Test Template
#section, then close the window used to
#create the form and proceed to insert it
#where the user wants it to go.
If [ $insertFormInPreviewWindow = "" ]
Close Window [ Current Window ]
End If
#
#If the user is in the test section, then go the
#Test window to add the form to the current
#result.
If [ Left (Get (LayoutName) ; 5 ) ≠ "setup" ]
If [ $report = 1 ]
Select Window [ Name: "Report"; Current file ]
Else
Select Window [ Name: "Test"; Current file ]
End If
End If
#
#If the note field is blank, then add the form to it.
If [ $note = "" ]
If [ $report = 1 ]
Set Field [ $form & $clearFormatting & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & $clearFormatting ]
Else
Set Field [ testlearn::note; $form & $clearFormatting & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & $clearFormatting ]
End If
#
#If it is not blank, then add the form below
#the curren text.
Else
If [ $report = 1 ]
Set Field [ $note & ¶ & $form & $clearFormatting & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & $clearFormatting ]
Else
Set Field [ testlearn::note; $note & ¶ & $form & $clearFormatting & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ & ¶ &
$clearFormatting ]
End If
End If
#
#
#END Insert form in designated field.
#
#
