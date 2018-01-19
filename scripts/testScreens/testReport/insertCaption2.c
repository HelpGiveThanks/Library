testScreens: testReport: insertCaption2
If [ report::_kfPhoto2 ≠ "" ]
Set Field [ report::PictureCaption[2]; testlearnReportTags 2::Caption ]
Go to Field [ ]
Else
Set Field [ report::PictureCaption[2]; "" ]
Go to Field [ ]
End If
August 20, ଘ౮28 14:28:39 Library.fp7 - insertCaption2 -1-
