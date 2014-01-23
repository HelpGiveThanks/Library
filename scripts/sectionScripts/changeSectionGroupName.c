sectionScripts: changeSectionGroupName
#
#
If [ $$stopChangeName = 1 ]
Set Variable [ $$stopChangeName ]
Exit Script [ ]
End If
#
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $$IDrecord; Value:test::_Ltest ]
Set Variable [ $$stopTest; Value:1 ]
Commit Records/Requests
Set Variable [ $name; Value:groupTest::name ]
Set Field [ groupTest::name; $name ]
Set Variable [ $section; Value:groupTest::ksection ]
New Window [ Height: 1; Width: 1; Top: 1; Left: 1 ]
Go to Layout [ “tableGroupTag” (groupTest) ]
#
Enter Find Mode [ ]
Set Field [ groupTest::match; "testGroup" ]
Set Field [ groupTest::name; "==" & $name ]
Set Field [ groupTest::ksection; $section ]
Perform Find [ ]
Set Variable [ $count; Value:Get (FoundCount) ]
Close Window [ Current Window ]
Set Variable [ $$ID; Value:$$IDrecord ]
If [ $count ≠ 1 ]
Show Custom Dialog [ Title: "!"; Message: "Each section group must have a unique name."; Buttons: “OK” ]
Set Field [ groupTest::name; $name & " " & groupTest::_Lgroup ]
Set Field [ groupTest::nameSpelling; $name & " " & groupTest::_Lgroup ]
Go to Field [ ]
Exit Script [ ]
End If
Set Field [ groupTest::nameSpelling; $name ]
Go to Field [ ]
Set Variable [ $$stopTest ]
January 7, 平成26 12:12:08 Imagination Quality Management.fp7 - changeSectionGroupName -1-
