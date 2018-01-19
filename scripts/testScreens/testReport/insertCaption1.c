testScreens: testReport: insertCaption1
If [ report::_kfPhoto ≠ "" ]
Set Field [ report::PictureCaption; testlearnReportTags::Caption ]
Go to Field [ ]
Else
Set Field [ report::PictureCaption; "" ]
Go to Field [ ]
End If
August 20, ଘ౮28 14:27:22 Library.fp7 - insertCaption1 -1-
