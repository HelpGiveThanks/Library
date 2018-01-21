January 21, 2018 11:02:39 Library.fmp12 - insertCaption4 -1-
test: report: insertCaption4
If [ report::kTag4 ≠ "" ]
Set Field [ report::PictureCaptionInsteadOfPicture[4]; testlearnReportTags 4::note ]
Go to Field [ ]
Else
Set Field [ report::PictureCaptionInsteadOfPicture[4]; "" ]
Go to Field [ ]
End If
