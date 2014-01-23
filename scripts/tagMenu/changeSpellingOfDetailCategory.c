tagMenu: changeSpellingOfDetailCategory
#
#If user approved spelling for this tag and no
#changes have been made then cancel the script.
If [ ruleTagMenuTestGroups::name = ruleTagMenuTestGroups::nameSpelling ]
Exit Script [ ]
End If
#
#Commit changes to the spellling.
Commit Records/Requests
Set Variable [ $newSpelling; Value:ruleTagMenuTestGroups::name ]
Set Variable [ $match; Value:ruleTagMenuTestGroups::match ]
#
#Check if a tag with this spelling already exists
#in the library.
New Window [ ]
Go to Layout [ “tableGroupTag” (groupTest) ]
#
Enter Find Mode [ ]
Set Field [ groupTest::name; "==" & $newSpelling ]
Set Field [ groupTest::match; $Match ]
Perform Find [ ]
#
If [ Get (FoundCount) > 1 ]
#Ask question.
Close Window [ Current Window ]
Set Field [ ruleTagMenuTestGroups::name; ruleTagMenuTestGroups::nameSpelling ]
Show Custom Dialog [ Message: "'" & $newSpelling & "' already exists. Each category for " & TEMP::testName & " must have a unique name. Change the spelling or cancel the change."; Buttons: “change”, “cancel”; Input #1: ruleTagMenuTestGroups::name ]
#
#
#Choice 1, user wants to change spelling.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $newSpelling ]
Perform Script [ “changeSpellingOfDetailCategory” ]
Exit Script [ ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
End If
#
#If the spellling of the tag has changed or if new tag
#update spelling of word in case of future changes
#to its spelling that would then trigger the ﬁrst
#part of this scirpt to udpate the spelling in the
#tag list.
Close Window [ Current Window ]
Set Field [ ruleTagMenuTestGroups::nameSpelling; $newSpelling ]
January 7, 平成26 16:31:38 Imagination Quality Management.fp7 - changeSpellingOfDetailCategory -1-
