testScreens: testReport: insertCaption3
If [ report::_kfPhoto3 ≠ "" ]
Set Field [ report::PictureCaption[3]; testlearnReportTags 3::Caption ]
Go to Field [ ]
Else
Set Field [ report::PictureCaption[3]; "" ]
Go to Field [ ]
End If
August 20, ଘ౮28 14:30:05 Library.fp7 - insertCaption3 -1-
