testScreens: testReport: insertCaption4
If [ report::_kfPhoto4 ≠ "" ]
Set Field [ report::PictureCaption[4]; testlearnReportTags 4::Caption ]
Go to Field [ ]
Else
Set Field [ report::PictureCaption[4]; "" ]
Go to Field [ ]
End If
August 20, ଘ౮28 14:31:00 Library.fp7 - insertCaption4 -1-
