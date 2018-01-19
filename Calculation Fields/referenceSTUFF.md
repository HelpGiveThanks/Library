//Keyword
If ( Title ≠ "" ; Title & " " ; "" )  &

//Keyword Group Label
TextColor (  

If ( kkeywordPrimary = "" ; "" ;  tagKeywordPrimary::tag ) &

If ( kkeywordOther = "" ; "" ; ", " & OtherKeyWords )

; If ( reference::_Lreference  = $$cite  and $$citationMatch = "cite" and $$internal = "" or

reference::_Lreference & "¶"  = FilterValues ( $$ref ; reference::_Lreference & "¶" )  and $$citationMatch = "ref" and $$internal = ""   ;

RGB ( 200 ; 200 ; 200 ) ; RGB ( 130 ; 130 ; 130 ) ) )
