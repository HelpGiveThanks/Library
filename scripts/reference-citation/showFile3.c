reference(citation): showFile3
#
#Show reference ﬁle.
If [ FilterValues ( citationTitle3::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationTitle3::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Else If [ FilterValues ( citationTitle3::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationTitle3::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationTitle3::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( tagFolderPathForFile3::tag & citationTitle3::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Else If [ citationTitle3::URL ≠ "" ]
Open URL [ citationTitle3::URL ]
[ No dialog ]
End If
#
#Show testlearn ﬁle.
If [ FilterValues ( TLTitle3::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLTitle3::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Else If [ FilterValues ( TLTitle3::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute (Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLTitle3::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLTitle3::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( tagTLFolderPathForFile3::tag & TLTitle3::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Else If [ TLTitle3::URL ≠ "" ]
Open URL [ TLTitle3::URL ]
[ No dialog ]
End If
January 7, 平成26 17:56:35 Imagination Quality Management.fp7 - showFile3 -1-
