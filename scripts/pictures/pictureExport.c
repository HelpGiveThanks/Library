July 20, 2018 21:32:09 Library.fmp12 - pictureExport -1-
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
Else If [ refLearnShowMedia::picture ≠ "" ]
Export Field Contents [ refLearnShowMedia::picture ]
End If
