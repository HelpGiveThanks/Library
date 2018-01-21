January 21, 2018 11:01:09 Library.fmp12 - insertCaption2 -1-
test: report: insertCaption2
If [ report::kTag2 ≠ "" ]
Set Field [ report::PictureCaptionInsteadOfPicture[2]; testlearnReportTags 2::note ]
Go to Field [ ]
Else
Set Field [ report::PictureCaptionInsteadOfPicture[2]; "" ]
Go to Field [ ]
End If
