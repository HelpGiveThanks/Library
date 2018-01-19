testScreens: testReport: inUsePart1
#
If [ $$finding ≠ "" ]
Set Variable [ $$Finding ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Report"; Current file ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
If [ testlearnReportTags::ktestSubject & $$reportNumber & "¶" = FilterValues ( testlearnReportTags::inUse ; $$contact & $
$reportNumber) ]
Go to Field [ ]
Show Custom Dialog [ Title: "!"; Message: "Already in use on this section of the report. Click on " & testlearnReportTags::
_Number & " on the Report screen to begin the process of moving it to a different slot. Click on a different slot to complete
the move."; Buttons: “OK” ]
Halt Script
End If
Set Variable [ $$finding; Value:testlearnReportTags::_Ltestlearn ]
Set Variable [ $$findingCaption; Value:testlearnReportTags::Caption ]
Set Variable [ $$window; Value:"Tag Menus" ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Report"; Current file ]
Refresh Window
#
August 19, ଘ౮28 19:22:15 Library.fp7 - inUsePart1 -1-
