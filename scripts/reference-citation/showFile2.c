reference(citation): showFile2
#
#Show reference ﬁle.
If [ FilterValues ( citationTitle2::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & citationTitle2::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Else If [ FilterValues ( citationTitle2::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & citationTitle2::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( citationTitle2::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( tagFolderPathForFile::tag & citationTitle2::ﬁleName ; " " ; "%20" ) ]
[ No dialog ]
Else If [ citationTitle2::URL ≠ "" ]
Open URL [ citationTitle2::URL ]
[ No dialog ]
End If
#
#Show testlearn ﬁle.
If [ FilterValues ( TLTitle2::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & "x/" & TLTitle2::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Else If [ FilterValues ( TLTitle2::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "ﬁle:" ; "ﬁle:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 9) & TLTitle2::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Exit Script [ ]
Else If [ FilterValues ( TLTitle2::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
Open URL [ Substitute ( tagTLFolderPathForFile2::tag & TLTitle2::ﬁlename ; " " ; "%20" ) ]
[ No dialog ]
Else If [ TLTitle2::URL ≠ "" ]
Open URL [ TLTitle2::URL ]
[ No dialog ]
End If
January 7, 平成26 17:56:07 Imagination Quality Management.fp7 - showFile2 -1-
