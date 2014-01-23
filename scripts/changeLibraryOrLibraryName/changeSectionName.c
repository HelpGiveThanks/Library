changeLibraryOrLibraryName: changeSectionName
If [ $$stopChangeSectionName ≠ 1 ]
Commit Records/Requests
Set Variable [ $name; Value:ruleSection::name ]
New Window [ ]
Go to Layout [ “tableGroupTag” (groupTest) ]
#
Enter Find Mode [ ]
Set Field [ groupTest::match; "section" ]
Set Field [ groupTest::name; "==" & $name ]
Perform Find [ ]
Set Variable [ $count; Value:Get (FoundCount) ]
Close Window [ Current Window ]
If [ $count ≠ 1 ]
Show Custom Dialog [ Title: "!"; Message: "Each section must have a unique name."; Buttons: “OK” ]
Set Field [ ruleSection::name; $name & " " & ruleSection::_Lgroup ]
Set Field [ ruleSection::nameSpelling; $name & " " & ruleSection::_Lgroup ]
Exit Script [ ]
End If
Go to Field [ ]
End If
January 7, 平成26 12:08:14 Imagination Quality Management.fp7 - changeSectionName -1-
