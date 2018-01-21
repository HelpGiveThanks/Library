January 20, 2018 17:50:26 Library.fmp12 - checkTagGroupNamesEXCEPTtestItemGroups -1-
tagMenu: checkTagGroupNamesEXCEPTtestItemGroups
#
#Stop script to speed up other scripts.
If [ $$stopChangeSpellingOfTagCategory ≠ "" ]
Set Variable [ $$stopChangeSpellingOfTagCategory ]
Exit Script [ ]
End If
#
#Copyright locked group name? Change back.
If [ tagMenuGroup::name ≠ tagMenuGroup::nameSpellingEXCEPTForTestItemGroup
and
tagMenuGroup::orderOrLibraryType ≠ ""
and
tagMenuGroup::match = "copyright"
or
tagMenuGroup::name ≠ tagMenuGroup::nameSpellingEXCEPTForTestItemGroup
and
Get (ActiveFieldName) ≠ "name"
and
tagMenuGroup::match = "copyright" ]
Set Field [ tagMenuGroup::name; tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ]
If [ Get (ActiveFieldName) = "name" ]
Show Custom Dialog [ Message: "Group name locked by system admin. "; Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
End If
#
#First turn back any spelling changes made by dragging
#text into field.
If [ $$citationMatch ≠ "copyright" ]
Set Variable [ $$tag; Value:tagMenuGroup::_Lgroup ]
Perform Script [ “CHUNKcheckForDragPasteChanges (update)” ]
Set Variable [ $$tag ]
End If
#
#If node is currenlty locked then stop script, inform user.
If [ nodeLockTagGroupCreatorLock::orderOrLock ≠ "" ]
Set Field [ tagMenuGroup::name; tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ]
Go to Field [ ]
If [ $$citationMatch ≠ "copyright" ]
Show Custom Dialog [ Message: "The node that created this — " & nodeLockTagGroupCreatorLock::tag & " — is locked.
Select this node in the setup window and enter the password to unlock it, then you will able to edit records assigned to
it."; Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
End If
#
#If user approved spelling for this tag and no
#changes have been made then cancel the script.
If [ tagMenuGroup::name = tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ]
Exit Script [ ]
End If
#
#Commit changes to the spellling.
Commit Records/Requests
Set Variable [ $newSpelling; Value:tagMenuGroup::name ]
#
#Check if a tag with this spelling already exists
#in the library. Stop error capture in case spelling
#is unique and thus no records will be found.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::name; "==" & $newSpelling ]
Set Field [ testSubsectionGroup::match; $$citationMatch ]
Perform Find [ ]
Set Variable [ $$stopLoadTagRecord ]
#
#If a duplicate is found...
If [ Get (FoundCount) > 1 ]
#
#Ask question.
Close Window [ Current Window ]
Set Field [ tagMenuGroup::name; tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ]
Show Custom Dialog [ Message: "The '" & $newSpelling & "' group already exists. Except for test-item groups, all other groups
must have unique names. Type a different name or cancel this change."; Default Button: “OK”, Commit: “Yes”; Button 2:
“cancel”, Commit: “No”; Input #1: tagMenuGroup::name ]
#
#Choice 1, user wants to change
#duplicate's spelling.
If [ Get ( LastMessageChoice ) = 1 ]
Commit Records/Requests
#
#If change was made to a new tag check
#if spelling is already in use.
Set Variable [ $newSpelling; Value:tagMenus::tag ]
Perform Script [ “checkTagGroupNamesEXCEPTtestItemGroups (update)” ]
#
#Exit script, otherwise main and tag
#menu windows will be closed.
Exit Script [ ]
#
#Choice 2 ...
Else If [ Get ( LastMessageChoice ) = 2 ]
#Exit script as no changes are being made,
#and to prevent the tag menus window
#being closed.
Exit Script [ ]
End If
End If
#
#If the spellling of the tag has changed or if new tag
#update spelling of word in case of future changes
#to its spelling that would then trigger the first
#part of this scirpt to udpate the spelling in the
#tag list.
Close Window [ Current Window ]
#
#All tests pasted? Accept user's change.
If [ $$citationMatch = "testItem" ]
Set Field [ tagMenuGroup::nameSpellingFORTestItemGroup; $newSpelling ]
Else
Set Field [ tagMenuGroup::nameSpellingEXCEPTForTestItemGroup; $newSpelling ]
End If
#
#
