January 15, 2018 16:51:10 Library.fmp12 - loadTestTagMenu -1-
tagMenu: loadTestTagMenu
If [ $$ID = testSubsectionTemplate::_LtestSubsection
 or
$$ID = "ignore" ]
Exit Script [ ]
End If
Go to Field [ ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Set Variable [ $subsectionName; Value:testSubsectionTemplate::name ]
Set Field [ TEMP::ktestSubsection; testSubsectionTemplate::_LtestSubsection ]
Set Field [ TEMP::testSubsectionName; testSubsectionTemplate::name ]
