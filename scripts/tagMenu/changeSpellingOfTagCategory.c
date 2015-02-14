tagMenu: changeSpellingOfTagCategory
#
#Stop script to speed up other scripts.
If [ $$stopChangeSpellingOfTagCategory ≠ "" ]
Set Variable [ $$stopChangeSpellingOfTagCategory ]
Exit Script [ ]
End If
#
#First turn back any spelling changes made by dragging
#text into field.
Set Variable [ $$tag; Value:ruleTagMenuGroups::_Lgroup ]
Perform Script [ “CHUNKcheckForDragPasteChanges” ]
Set Variable [ $$tag ]
#
#If node is currenlty locked then stop script, inform user.
If [ nodeLockTagMenus::orderOrLock ≠ "" ]
Set Field [ ruleTagMenuGroups::name; ruleTagMenuGroups::nameSpelling ]
Go to Field [ ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to edit records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If user approved spelling for this tag and no
#changes have been made then cancel the script.
If [ ruleTagMenuGroups::name = ruleTagMenuGroups::nameSpelling ]
Exit Script [ ]
End If
#
#Commit changes to the spellling.
Commit Records/Requests
Set Variable [ $newSpelling; Value:ruleTagMenuGroups::name ]
#
#Check if a tag with this spelling already exists
#in the library. Stop error capture in case spelling
#is unique and thus no records will be found.
New Window [ ]
Go to Layout [ “tableGroupTag” (groupTest) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
Enter Find Mode [ ]
Set Field [ groupTest::name; "==" & $newSpelling ]
Set Field [ groupTest::match; $$citationMatch ]
Perform Find [ ]
#
If [ Get (FoundCount) > 1 ]
#Ask question.
Close Window [ Current Window ]
Set Field [ ruleTagMenuGroups::name; ruleTagMenuGroups::nameSpelling ]
Show Custom Dialog [ Message: "'" & $newSpelling & "' already exists in library. Each category in the " & $$citationMatch & " must have a unique name. Change the spelling or cancel the change."; Buttons: “change”, “cancel”; Input #1: ruleTagMenuGroups::name ]
#
#
#Choice 1, user wants to change spelling.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $newSpelling ]
Perform Script [ “changeSpellingOfTagCategory” ]
Else If [ Get ( LastMessageChoice ) = 2 ]
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
Set Field [ ruleTagMenuGroups::nameSpelling; $newSpelling ]
January 7, 平成26 16:31:08 Imagination Quality Management.fp7 - changeSpellingOfTagCategory -1-
