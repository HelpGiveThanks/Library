January 15, 2018 17:42:57 Library.fmp12 - pictureExport -1-
pictures: pictureExport
Allow User Abort [ Off ]
Set Error Capture [ On ]
If [ reference::picture ≠ "" ]
#
#
#If a creative commons trademark then the user needs to get a new copy of the file from the web.
#
#
#
Show Custom Dialog [ ]
Export Field Contents [ reference::picture ]
Else If [ testlearn::picture ≠ "" ]
Export Field Contents [ testlearn::picture ]
Else If [ testlearnReportTags::picture ≠ "" ]
Export Field Contents [ testlearnReportTags::picture ]
End If
