January 20, 2018 18:25:18 Library.fmp12 - brainstormExit -1-
tagMenu: brainstormExit
If [ $$citationMatch = "brainstorm" and $$findMode = "" or
$$citationmatch = "test" and $$findMode = "" ]
Set Variable [ $$stopTgotoCitationMenu ]
Go to Field [ ]
Exit Script [ ]
End If
If [ Get (WindowName) = "Tag Menus" ]
Set Field [ testlearnReportTags::orderTestInformation; "" ]
Else
Set Field [ testlearn::orderTestInformation; "" ]
End If
Set Variable [ $$orderNumbersNotAllowed; Value:1 ]
Go to Field [ ]
