January 21, 2018 11:00:22 Library.fmp12 - insertCaption1 -1-
test: report: insertCaption1
If [ report::kTag1 ≠ "" ]
Set Field [ report::PictureCaptionInsteadOfPicture; testlearnReportTags::note ]
Go to Field [ ]
Else
Set Field [ report::PictureCaptionInsteadOfPicture; "" ]
Go to Field [ ]
End If
