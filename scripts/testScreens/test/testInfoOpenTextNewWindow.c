testScreens: test: TestInfoOpenTextNewWindow
If [ $$stopOpenNewTextWindow = 1 ]
Set Variable [ $$stopOpenNewTextWindow ]
Exit Script [ ]
End If
Go to Field [ ]
Set Variable [ $$stopLoadCitation; Value:1 ]
New Window [ ]
If [ tagTLNodePrimary::orderOrLock = "" and Get (LayoutName) ≠ "testInfo" ]
Scroll Window
[ Home ]
Go to Layout [ “testInfoText” (testlearnReportTags) ]
// Go to Field [ testlearnReportTags::Caption ]
Else If [ tagTLNodePrimary 2::orderOrLock = "" ]
Scroll Window
[ Home ]
Go to Layout [ “testInfoText” (testlearnReportTags) ]
// Go to Field [ testlearnReportTags::Caption ]
Else If [ tagTLNodePrimary::orderOrLock ≠ "" or tagTLNodePrimary 2::orderOrLock ≠ "" ]
Go to Layout [ “testInfoTextLocked” (testlearnReportTags) ]
End If
Set Variable [ $$stopLoadCitation ]
Pause/Resume Script [ Indeﬁnitely ]
January 7, 平成26 12:22:08 Imagination Quality Management.fp7 - TestInfoOpenTextNewWindow -1-
