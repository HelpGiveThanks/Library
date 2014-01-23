pictures: pictureExport
Allow User Abort [ Off ]
Set Error Capture [ On ]
If [ reference::picture ≠ "" ]
Export Field Contents [ reference::picture ]
Else If [ testlearn::Picture ≠ "" ]
Export Field Contents [ testlearn::Picture ]
Else If [ testlearnReportTags::Picture ≠ "" ]
Export Field Contents [ testlearnReportTags::Picture ]
End If
January 7, 平成26 17:06:11 Imagination Quality Management.fp7 - pictureExport -1-
