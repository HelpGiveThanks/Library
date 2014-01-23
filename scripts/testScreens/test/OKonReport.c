testScreens: test: OKonReport
If [ testlearnReportTags::OK = "" ]
Set Field [ testlearnReportTags::OK; TextSize ( "☺" ; 30 ) ]
Go to Field [ ]
Exit Script [ ]
Else If [ testlearnReportTags::OK = "☺" ]
Set Field [ testlearnReportTags::OK;
TextStyleAdd ( TextSize ( "⚇"; 75 ) ; Superscript ) ]
Go to Field [ ]
Exit Script [ ]
Else If [ testlearnReportTags::OK = "⚇" ]
Set Field [ testlearnReportTags::OK; "☹" ]
Go to Field [ ]
Exit Script [ ]
End If
Set Field [ testlearnReportTags::OK; "" ]
Go to Field [ ]
January 7, 平成26 12:41:08 Imagination Quality Management.fp7 - OKonReport -1-
