using System;
using System.Runtime.InteropServices;

namespace libPac_Cs
{
    public static class Pac
    {
        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
#if UNITY_STANDALONE_LINUX
            EntryPoint = "_Z15extract_archivePKcS0_")]
#else
            EntryPoint = "?extract_archive@@YAXPBD0@Z")]
#endif
        public static extern void extract_archive(String pac, String folder = "");

                [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
#if UNITY_STANDALONE_LINUX
            EntryPoint = "_Z24extract_archive_withlistPKcS0_PPci")]
#else
            EntryPoint = "?extract_archive_withlist@@YAXPBDPAPADH0@Z")]
#endif
        public static extern void extract_archive_withlist(String pac, String[] ListOfFiles, int numoffiles, String folder = "");

        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
#if UNITY_STANDALONE_LINUX
            EntryPoint = "_Z12pack_archivePKc")]
#else
            EntryPoint = "?pack_archive@@YAXPBD@Z")]
#endif
        public static extern void pack_archive(String path);

        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
#if UNITY_STANDALONE_LINUX
            EntryPoint = "_Z13patch_archivePKcS0_")]
#else
            EntryPoint = "?patch_archive@@YAXPBD0@Z")]
#endif
        public static extern void patch_archive(String pac, String folder = "");

#if UNITY_EDITOR || DEBUG
        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
#if UNITY_STANDALONE_LINUX
            EntryPoint = "_Z8testpathPKc")]
#else
            EntryPoint = "_Z12pack_archivePKc")]
#endif
        public static extern void testpath(String path);

        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
#if UNITY_STANDALONE_LINUX
            EntryPoint = "_Z7testlibPKc")]
#else
            EntryPoint = "_Z12pack_archivePKc")]
#endif
        public static extern void testlib(String path);
#endif
    }
}