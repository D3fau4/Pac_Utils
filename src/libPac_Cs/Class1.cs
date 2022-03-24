using System;
using System.Runtime.InteropServices;

namespace libPac_Cs
{
    public static class Class1
    {
#if UNITY_STANDALONE || UNITY_EDITOR_64 || UNITY_STANDALONE_LINUX || DEBUG
    [DllImport(LibPac.DllName,
#if UNITY_STANDALONE_LINUX
            CallingConvention = CallingConvention.FastCall,
#else
            CallingConvention = CallingConvention.Cdecl,
#endif
            EntryPoint = "testlib")]
    public static extern void testlib();
#endif
    }
}
