January 21, 2018 11:01:52 Library.fmp12 - insertCaption3 -1-
test: report: insertCaption3
If [ report::kTag3 ≠ "" ]
Set Field [ report::PictureCaptionInsteadOfPicture[3]; testlearnReportTags 3::note ]
Go to Field [ ]
Else
Set Field [ report::PictureCaptionInsteadOfPicture[3]; "" ]
Go to Field [ ]
End If
