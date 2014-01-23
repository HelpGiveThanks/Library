testScreens: test: OKonInpsection
If [ testlearn::OK = "" ]
Set Field [ testlearn::OK; TextSize ( "☺" ; 42 ) ]
Go to Field [ ]
Exit Script [ ]
Else If [ testlearn::OK = "☺" ]
Set Field [ testlearn::OK;
TextSize ( "⚇"; 50 ) ]
Go to Field [ ]
Exit Script [ ]
Else If [ testlearn::OK = "⚇" ]
Set Field [ testlearn::OK; "☹" ]
Go to Field [ ]
Exit Script [ ]
End If
Set Field [ testlearn::OK; "" ]
Go to Field [ ]
January 7, 平成26 12:39:56 Imagination Quality Management.fp7 - OKonInpsection -1-
