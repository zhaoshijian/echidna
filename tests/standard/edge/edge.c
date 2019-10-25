#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <runtime.h>

#include <suite.h>

//  xxd -i src/edge.txt

static char _Source[] = {
    0x50, 0x52, 0x4f, 0x47, 0x52, 0x41, 0x4d, 0x20, 
    0x74, 0x65, 0x73, 0x74, 0x0a, 0x56, 0x41, 0x52, 
    0x20, 0x69, 0x31, 0x2c, 0x20, 0x69, 0x32, 0x3a, 
    0x20, 0x42, 0x4f, 0x4f, 0x4c, 0x20, 0x3a, 0x3d, 
    0x20, 0x46, 0x41, 0x4c, 0x53, 0x45, 0x3b, 0x20, 
    0x45, 0x4e, 0x44, 0x5f, 0x56, 0x41, 0x52, 0x0a, 
    0x56, 0x41, 0x52, 0x20, 0x63, 0x6f, 0x75, 0x6e, 
    0x74, 0x3a, 0x20, 0x55, 0x4c, 0x49, 0x4e, 0x54, 
    0x20, 0x3a, 0x3d, 0x20, 0x30, 0x3b, 0x20, 0x45, 
    0x4e, 0x44, 0x5f, 0x56, 0x41, 0x52, 0x0a, 0x56, 
    0x41, 0x52, 0x20, 0x66, 0x65, 0x64, 0x67, 0x65, 
    0x3a, 0x20, 0x46, 0x5f, 0x54, 0x52, 0x49, 0x47, 
    0x3b, 0x20, 0x45, 0x4e, 0x44, 0x5f, 0x56, 0x41, 
    0x52, 0x0a, 0x56, 0x41, 0x52, 0x20, 0x72, 0x65, 
    0x64, 0x67, 0x65, 0x3a, 0x20, 0x52, 0x5f, 0x54, 
    0x52, 0x49, 0x47, 0x3b, 0x20, 0x45, 0x4e, 0x44, 
    0x5f, 0x56, 0x41, 0x52, 0x0a, 0x0a, 0x41, 0x44, 
    0x44, 0x20, 0x63, 0x6f, 0x75, 0x6e, 0x74, 0x2c, 
    0x20, 0x31, 0x0a, 0x53, 0x54, 0x20, 0x63, 0x6f, 
    0x75, 0x6e, 0x74, 0x0a, 0x0a, 0x4c, 0x44, 0x20, 
    0x63, 0x6f, 0x75, 0x6e, 0x74, 0x0a, 0x4d, 0x4f, 
    0x44, 0x20, 0x33, 0x0a, 0x45, 0x51, 0x20, 0x30, 
    0x0a, 0x53, 0x54, 0x20, 0x69, 0x31, 0x0a, 0x43, 
    0x41, 0x4c, 0x20, 0x72, 0x65, 0x64, 0x67, 0x65, 
    0x28, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x43, 0x4c, 
    0x4b, 0x20, 0x3a, 0x3d, 0x20, 0x69, 0x31, 0x0a, 
    0x29, 0x0a, 0x0a, 0x4c, 0x44, 0x20, 0x63, 0x6f, 
    0x75, 0x6e, 0x74, 0x0a, 0x4d, 0x4f, 0x44, 0x20, 
    0x35, 0x0a, 0x4e, 0x45, 0x20, 0x30, 0x0a, 0x53, 
    0x54, 0x20, 0x69, 0x32, 0x0a, 0x43, 0x41, 0x4c, 
    0x20, 0x66, 0x65, 0x64, 0x67, 0x65, 0x28, 0x0a, 
    0x20, 0x20, 0x20, 0x20, 0x43, 0x4c, 0x4b, 0x20, 
    0x3a, 0x3d, 0x20, 0x69, 0x32, 0x0a, 0x29, 0x0a, 
    0x0a, 0x4c, 0x44, 0x20, 0x66, 0x65, 0x64, 0x67, 
    0x65, 0x2e, 0x51, 0x0a, 0x41, 0x4e, 0x44, 0x20, 
    0x72, 0x65, 0x64, 0x67, 0x65, 0x2e, 0x51, 0x0a, 
    0x52, 0x45, 0x54, 0x43, 0x4e, 0x0a, 0x5f, 0x65, 
    0x78, 0x69, 0x74, 0x0a, 0x0a, 0x45, 0x4e, 0x44, 
    0x5f, 0x50, 0x52, 0x4f, 0x47, 0x52, 0x41, 0x4d, 
    0x0a, 0x0a, 0x43, 0x4f, 0x4e, 0x46, 0x49, 0x47, 
    0x55, 0x52, 0x41, 0x54, 0x49, 0x4f, 0x4e, 0x20, 
    0x63, 0x6f, 0x6e, 0x66, 0x69, 0x67, 0x31, 0x0a, 
    0x54, 0x41, 0x53, 0x4b, 0x20, 0x74, 0x61, 0x73, 
    0x6b, 0x31, 0x20, 0x28, 0x50, 0x52, 0x49, 0x4f, 
    0x52, 0x49, 0x54, 0x59, 0x20, 0x3a, 0x3d, 0x20, 
    0x31, 0x29, 0x3b, 0x0a, 0x50, 0x52, 0x4f, 0x47, 
    0x52, 0x41, 0x4d, 0x20, 0x70, 0x72, 0x6f, 0x67, 
    0x72, 0x61, 0x6d, 0x31, 0x3a, 0x20, 0x74, 0x65, 
    0x73, 0x74, 0x3b, 0x0a, 0x45, 0x4e, 0x44, 0x5f, 
    0x43, 0x4f, 0x4e, 0x46, 0x49, 0x47, 0x55, 0x52, 
    0x41, 0x54, 0x49, 0x4f, 0x4e, 0x0a, 0x00
};


MunitResult 
test_edge(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    munit_assert_int(test_parse(pContext, _Source), ==, 0);
    function_table_build(&pContext->Functions);
    pContext->Option |= (OPTION_COMPILE | OPTION_RUN);
    pContext->Output = NULL;
    munit_assert_int(echidna_compile(pContext), ==, 0);
    munit_assert_int(echidna_run(pContext), ==, 0);

    return MUNIT_OK;
}


