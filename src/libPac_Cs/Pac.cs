using System;
using System.Runtime.InteropServices;

namespace libPac_Cs
{
    public static class Pac
    {
        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
#if UNITY_STANDALONE_LINUX
            EntryPoint = "_Z15extract_archivePKc")]
#else
            EntryPoint = "?extract_archive@@YAXPBD@Z")]
#endif
        public static extern void extract_archive(String path);

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
            EntryPoint = "_Z13patch_archivePKc")]
#else
            EntryPoint = "?patch_archive@@YAXPBD@Z")]
#endif
        public static extern void patch_archive(String path);

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