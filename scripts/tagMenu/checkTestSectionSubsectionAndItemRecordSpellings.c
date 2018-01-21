January 20, 2018 18:19:42 Library.fmp12 - checkTestSectionSubsectionAndItemRecordSpellings -1-
tagMenu: checkTestSectionSubsectionAndItemRecordSpellings
#
#
#Stop this script if any of the following
#are true.
If [ $$stopTest = 1
or $$userClickedVButton ≠ "" ]
Exit Script [ ]
End If
#
#
#BEGIN Tag menus layout check
#
#
If [ Get (LayoutTableName) = "tagMenus" ]
#
If [ $$tag = "" ]
Set Variable [ $otherTypeOfTag; Value:tagMenus::_Ltag ]
End If
#
#Exit any fields so do not get can't modify error message
#because record is in use in another window.
Go to Field [ ]
#
#Speed up script by stopping record load script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#New window so user's window is not changed.
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Top: 1; Left: 1; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
#
#Loop thru all records and make sure their spelling
#has not been changed, and if it has then change it back
#to the way it was, unless the change was made in the
#field the user was just working on.
Go to Record/Request/Page
[ First ]
Loop
#Test item group name.
If [ tagMenuTestItemGroup::name ≠ tagMenuTestItemGroup::nameSpellingFORTestItemGroup
and
tagMenuTestItemGroup::nameSpellingEXCEPTForTestItemGroup = "testItemGroup" ]
Set Field [ tagMenuTestItemGroup::name; tagMenuTestItemGroup::nameSpellingFORTestItemGroup ]
End If
#Brainstorm, copyright, node, key, publisher, publication, testItem locked group name.
If [ $$tag ≠ "" and $$tag ≠ tagMenuGroup::_Lgroup and tagMenuGroup::name ≠ tagMenuGroup::
nameSpellingEXCEPTForTestItemGroup ]
Set Field [ tagMenuGroup::name; tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ]
End If
#Brainstorm, copyright, node, key, publisher, publication, testItem tag names.
If [ $$tag ≠ "" and $$tag ≠ tagMenus::_Ltag
 or
$$tag = "" and $otherTypeOfTag ≠ tagMenus::_Ltag
 or
tagCreatorLock::orderOrLock ≠ "" ]
If [ tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::match = "testItem"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::match = "brainstorm"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::match = "copyright"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::match = "publication"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::match = "node"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::match = "publisher"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagMenus::match = "key" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
End If
End If
#Locked by system copyright tags.
If [ tagMenus::orderOrLock ≠ "" and tagMenus::match = "copyright" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
End If
#
#
#
#
#But if node is not locked and this is the tag
#the user just updated, then apply changes
#to tag.
#Group name.
If [ $$tag ≠ "" and $$tag = tagMenuGroup::_Lgroup and
tagMenuGroup::name ≠ tagMenuGroup::nameSpellingFORTestItemGroup
and
Get (LayoutTableName) = "testSubsection"
 and
tagCreatorLock::orderOrLock = "" and
tagMenuGroup::match = "testSubsection" ]
Set Field [ tagMenuGroup::nameSpellingFORTestItemGroup; tagMenuGroup::name ]
End If
#Test item group name.
If [ $$tag ≠ "" and $$tag = tagMenuTestItemGroup::_Lgroup and
tagMenuTestItemGroup::name ≠ tagMenuTestItemGroup::nameSpellingFORTestItemGroup and
Get (LayoutTableName) ≠ "subsectionFromTemplate" and
tagMenuTestItemGroup::nameSpellingEXCEPTForTestItemGroup = "testItemGroup" ]
If [ $$citationMatch = "testItem" ]
Set Field [ tagMenuTestItemGroup::nameSpellingFORTestItemGroup; tagMenuTestItemGroup::name ]
End If
End If
#Brainstorm group name.
If [ $$tag ≠ "" and $$tag = tagMenuGroup::_Lgroup and tagMenuGroup::name ≠ tagMenuGroup::
nameSpellingEXCEPTForTestItemGroup
and
tagMenuTestItemGroup::nameSpellingEXCEPTForTestItemGroup ≠ "testItemGroup" ]
If [ $$citationMatch ≠ "testItem" ]
Set Field [ tagMenuGroup::nameSpellingEXCEPTForTestItemGroup; tagMenuGroup::name ]
End If
End If
#Brainstorm, copyright, node, publisher, publication, testItem, key, tag names.
If [ $$tag = tagMenus::_Ltag
 or
$$tag = "" and $otherTypeOfTag = tagMenus::_Ltag ]
If [ tagMenus::tag ≠ tagMenus::tagSpelling and tagCreatorLock::orderOrLock = "" and tagMenus::match = "testItem"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagCreatorLock::orderOrLock = "" and tagMenus::match =
"brainstorm"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagCreatorLock::orderOrLock = "" and tagMenus::match =
"copyright"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagCreatorLock::orderOrLock = "" and tagMenus::match =
"publication"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagCreatorLock::orderOrLock = "" and tagMenus::match =
"publisher"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagCreatorLock::orderOrLock = "" and tagMenus::match = "node"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagCreatorLock::orderOrLock = "" and tagMenus::match = "key"
 or tagMenus::tag ≠ tagMenus::tagSpelling and tagCreatorLock::orderOrLock = "" and tagMenus::match = "path" ]
Set Field [ tagMenus::tagSpelling; tagMenus::tag ]
End If
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start up record load script and close the window.
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopTest ]
Close Window [ Current Window ]
#
#
#END Tag menus layout check
#
#
#
#
#
#BEGIN Test subsection template layout check
#
#
Else If [ Get (LayoutTableName) = "testSubsectionTemplate" ]
#
#Get current group's record key.
If [ Get ( ActiveFieldTableName ) = "testSubsectionGroup" ]
Set Variable [ $subsectionGroupKey; Value:testSubsectionGroup::_Lgroup ]
#
#Also get subsection group's name if it has
#been changed, because below, this script will
#need to insure it is not a duplicate name.
If [ testSubsectionGroup::name ≠ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup and
testSubsectionGroupNodeLock::orderOrLock = "" ]
Set Variable [ $subsectionGroupName; Value:testSubsectionGroup::name ]
End If
#
#...OR...
#
#Get current subsection's record key.
Else If [ Get ( ActiveFieldTableName ) = "testSubsectionTemplate" ]
Set Variable [ $testSubsectionTemplateKey; Value:testSubsectionTemplate::_LtestSubsection ]
End If
#
#Exit any fields so we do not get a
#"can't modify" error message.
Set Variable [ $$stopChangeName; Value:1 ]
Go to Field [ ]
#
#Speed up script by stopping record load script.
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $$stopTest; Value:1 ]
#
#New window so user's window is not changed.
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#Loop thru all records and make sure their spelling
#has not been changed, and if it has change it back
#to the way it was, unless the change was made to the
#record the user was just working on.
Go to Record/Request/Page
[ First ]
Loop
#
#Undo changes to locked and not updated
#subsection group names.
If [ //Is group record's creator node locked?
testSubsectionGroup::name ≠ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup and
testSubsectionGroupNodeLock::orderOrLock ≠ "" and testSubsectionGroup::match = "testSubsection"
 or
//Is this subsection group's name NOT being actively edited?
$subsectionGroupKey ≠ testSubsectionGroup::_Lgroup and testSubsectionGroup::match = "testSubsection" ]
Set Field [ testSubsectionGroup::name; testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup ]
End If
#
#Undo changes to locked and not updated
#subsection names.
If [ //Is subsection record's creator node locked?
testSubsectionTemplate::name ≠ testSubsectionTemplate::nameSpelling and testSectionCreatorLock::orderOrLock ≠ ""
 or
//Is this subsection's name NOT being actively edited?
testSubsectionTemplate::name ≠ testSubsectionTemplate::nameSpelling and $testSubsectionTemplateKey ≠
testSubsectionTemplate::_LtestSubsection ]
Set Field [ testSubsectionTemplate::name; testSubsectionTemplate::nameSpelling ]
End If
#
#Update just updated subsection's name.
If [ //Is this subsection's name being actively edited?
testSubsectionTemplate::name ≠ testSubsectionTemplate::nameSpelling and testSectionCreatorLock::orderOrLock = ""
and $testSubsectionTemplateKey = testSubsectionTemplate::_LtestSubsection ]
Set Field [ testSubsectionTemplate::nameSpelling; testSubsectionTemplate::name ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If a subsection's group name was changed,
#make sure it is not a duplicate spelling.
If [ $subsectionGroupName ≠ "" ]
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::match; "testSubsection" ]
Set Field [ testSubsectionGroup::name; "==" & $subsectionGroupName ]
Perform Find [ ]
Set Variable [ $count; Value:Get (FoundCount) ]
End If
#
Close Window [ Current Window ]
#
#If subsection group is a duplicate then make
#it unique.
If [ $count > 1 ]
Set Field [ testSubsectionGroup::name; $subsectionGroupName & " " & testSubsectionGroup::_Lgroup ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $subsectionGroupName & " " &
testSubsectionGroup::_Lgroup ]
Commit Records/Requests
Show Custom Dialog [ Message: "Subsection groups must have unique names."; Default Button: “OK”, Commit: “Yes” ]
Go to Field [ ]
Scroll Window
[ Home ]
Sort Records [ ]
[ No dialog ]
#
#If subsection's group name is unique,
#then updage its spelling field.
Else If [ $count = 1 ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $subsectionGroupName ]
Go to Field [ ]
Scroll Window
[ Home ]
Sort Records [ ]
[ No dialog ]
End If
#
#Start up record load script.
Set Variable [ $$ID ]
Set Variable [ $$stopTest ]
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadSetupTestSubsection (update name change loadSetupTestRecord)” ]
#
#
#END Test subsection template layout check
#
#
#
#
#
#BEGIN Test section template layout check
#
#
Else If [ Get (LayoutTableName) = "testSection" ]
#
#Get current section's record key.
Set Variable [ $testSectionTemplateKey; Value:testSection::_Ltag ]
#
#Exit any fields so do not get can't modify error message
#because record is in use in another window.
Go to Field [ ]
#
#Speed up script by stopping record load script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#New window so user's window is not changed.
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#Loop thru all records and make sure their spelling
#has not been changed, and if it has then change it back
#to the way it was, unless the change was made to the
#record the user was just working on.
Go to Record/Request/Page
[ First ]
Loop
#
#If the record's creator node is locked, or is
#not being actively updated, then revert any
#spelling changes.
If [ testSectionCreatorLock::orderOrLock ≠ ""
 or
$testSectionTemplateKey ≠ testSection::_Ltag ]
Set Field [ testSection::tag; testSection::tagSpelling ]
End If
#
#But if node is not locked, then apply changes to
#field user was just in if any changes where made.
If [ testSectionCreatorLock::orderOrLock = ""
 and
$testSectionTemplateKey = testSection::_Ltag ]
Set Field [ testSection::tagSpelling; testSection::tag ]
End If
#
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start up record load script and close the window.
Set Variable [ $$stopLoadTagRecord ]
Close Window [ Current Window ]
Set Variable [ $$stopTest ]
Set Variable [ $$ID ]
Exit Script [ ]
#
End If
#
#
#END Test section template layout check
#
#
