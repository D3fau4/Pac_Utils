using System;
using System.Runtime.InteropServices;

namespace libPac_Cs
{
    public static class Pac
    {
        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "_Z15extract_archivePKc")]
        public static extern void extract_archive(String path);

        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "_Z12pack_archivePKc")]
        public static extern void pack_archive(String path);

        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "_Z13patch_archivePKc")]
        public static extern void patch_archive(String path);

#if UNITY_EDITOR || DEBUG
        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "_Z8testpathPKc")]
        public static extern void testpath(String path);

        [DllImport(LibPac.DllName,
            CallingConvention = CallingConvention.Cdecl,
            EntryPoint = "_Z7testlibPKc")]
        public static extern void testlib(String path);
#endif
    }
}