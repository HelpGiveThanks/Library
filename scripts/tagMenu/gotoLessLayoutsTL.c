January 21, 2018 11:42:39 Library.fmp12 - gotoLessLayoutsTL -1-
tagMenu: gotoLessLayoutsTL
#
#Reveal more or fewer pictures and links for tag.
If [ Right ( Get (LayoutName) ; 8 ) = "evenmore" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learn5” (testlearn) ]
Else If [ Left (Get (LayoutName) ; 1) = "t" ]
End If
Else If [ Get (LayoutName) = "learnBigPicture" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learn3” (testlearn) ]
Else If [ Left (Get (LayoutName) ; 1) = "t" ]
End If
Else If [ Right ( Get (LayoutName) ; 4 ) = "more" and Right ( Get (LayoutName) ; 8 ) ≠ "evenmore" and Right ( Get (LayoutName) ; 10 )
≠ "BigPicture" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learn2” (testlearn) ]
Else If [ Left (Get (LayoutName) ; 1) = "t" ]
End If
End If
#
#Remember layout user is on so they can be
#returned to correct view.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Set Field [ TEMP::layoutLmain; Get (LayoutName) ]
Else If [ Left (Get (LayoutName) ; 1) = "t" ]
End If
