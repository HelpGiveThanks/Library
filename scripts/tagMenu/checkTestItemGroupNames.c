January 20, 2018 17:51:59 Library.fmp12 - checkTestItemGroupNames -1-
tagMenu: checkTestItemGroupNames
#
#If user approved spelling for this tag and no
#changes have been made then cancel the script.
If [ tagMenuTestItemGroup::name = tagMenuTestItemGroup::nameSpellingFORTestItemGroup ]
Perform Script [ “CHUNKcheckForDragPasteChanges (update)” ]
Exit Script [ ]
End If
#
#changes have been made then cancel the script.
If [ nodeLockTestTagItemGroup::orderOrLock ≠ "" ]
Set Field [ tagMenuTestItemGroup::name; tagMenuTestItemGroup::nameSpellingFORTestItemGroup ]
Perform Script [ “CHUNKcheckForDragPasteChanges (update)” ]
Exit Script [ ]
End If
#
#Commit changes to the spellling.
Commit Records/Requests
Set Variable [ $newSpelling; Value:tagMenuTestItemGroup::name ]
#
#Check if a tag with this spelling already exists
#in the library.
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
#
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::name; "==" & $newSpelling ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; "testItemGroup" ]
Perform Find [ ]
Set Variable [ $foundCount; Value:Get (FoundCount) ]
Close Window [ Current Window ]
#
If [ $foundCount > 1 ]
#Ask question.
Show Custom Dialog [ Message: "Click OK to approve the duplicate group spelling below. NOTE: When clicking the link button,
you will see " & $foundCount & " groups with this same name. To modify this group's name, make changes below, and click
change."; Default Button: “change”, Commit: “Yes”; Button 2: “OK”, Commit: “No”; Button 3: “cancel”, Commit: “No”; Input #1:
tagMenuTestItemGroup::name ]
#
#
#Choice 1, user wants to change spelling.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $newSpelling ]
Perform Script [ “checkTestItemGroupNamess (update)” ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Set Field [ tagMenuTestItemGroup::name; tagMenuTestItemGroup::nameSpellingFORTestItemGroup ]
Perform Script [ “CHUNKcheckForDragPasteChanges (update)” ]
Exit Script [ ]
End If
End If
#
#If the spellling of the tag has changed or if new tag
#update spelling of word in case of future changes
#to its spelling that would then trigger the first
#part of this scirpt to udpate the spelling in the
#tag list.
Set Field [ tagMenuTestItemGroup::nameSpellingFORTestItemGroup; $newSpelling ]
#
Perform Script [ “CHUNKcheckForDragPasteChanges (update)” ]
#
