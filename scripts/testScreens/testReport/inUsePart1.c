testScreens: testReport: InUsePart1
#
If [ $$ﬁnding ≠ "" ]
Set Variable [ $$Finding ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Report"; Current ﬁle ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Exit Script [ ]
End If
#
If [ testlearnReportTags::ktestSubject & $$reportNumber & "¶" = FilterValues ( testlearnReportTags::inUse ; $$contact & $$reportNumber) ]
Go to Field [ ]
Show Custom Dialog [ Title: "!"; Message: "Already in use on this section of the report. Click on " & testlearnReportTags::_Number & " on the Report screen to begin the process of moving it to a different slot. Click on a different slot to complete the move."; Buttons: “OK” ]
Halt Script
End If
Set Variable [ $$ﬁnding; Value:testlearnReportTags::_Ltestlearn ]
Set Variable [ $$window; Value:"Tag Menus" ]
Go to Field [ ]
Refresh Window
Select Window [ Name: "Report"; Current ﬁle ]
Refresh Window
#
January 7, 平成26 14:27:56 Imagination Quality Management.fp7 - InUsePart1 -1-
