#ifndef gl_States_h__
#define gl_States_h__

#include "gl_Core.h"

class gl_State : protected gl_Core
{
public:
    enum
    {
        FoggingEnabled,
        FoggingMode,
        FoggingEnd,
        FoggingDistance,
        FoggingColor,

        ScissorEnabled,
        ScissorArea,

        DepthBoundsTestEnabled,
        DepthBoundsTestBounds,
        
        AlphaTestEnabled,
        AlphaTestFunction,
        
        StencilTestEnabled,
        StencilTestFunction,
        StencilTestOperation,
        
        DepthTestEnabled,
        DepthTestFunc,
        
        BlendingEnabled,
        BlendingEquation,
        BlendingColor,
        
        DitheringEnabled,
        
        LogicalOperationEnabled,
        LogicalOperationFunction,

        LineSmoothEnabled,

        ActiveTexture,
        ActiveTexture0 = ActiveTexture,
        ActiveTexture1,
        ActiveTexture2,
        ActiveTexture3,
        ActiveTexture4,
        ActiveTexture5,
        ActiveTexture6,
        ActiveTexture7,

        StateCount
    };

protected:
    static __forceinline void Reset(u32 index)
    {
        assert(index < StateCount);

        m_active_changes[index] = 0;
    }

    static __forceinline void Update(u32 index)
    {
        assert(index < StateCount);

        m_active_changes[index]++;
    }

    static __forceinline bool Check(u32 index)
    {
        assert(index < StateCount);

        if (m_changes[index] != m_active_changes[index])
        {
            m_changes[index] = m_active_changes[index];

            return true;
        }

        return false;
    }

    static __forceinline GLenum const TFUNC(u8 index)
    {
        assert(index < 8);
        static GLenum const translate[8] = { NEVER, ALWAYS, EQUAL, NOTEQUAL, LESS, LEQUAL, GREATER, GEQUAL };
        return translate[index];
    }

    static u8 m_changes[StateCount];
    static u8 m_active_changes[StateCount];
};


template< typename Type, u32 state >
class gl_StateProperty1 : protected gl_State
{
public:
    void operator () (Type const value)          { this->operator = (value); }
    void operator = (Type const value)           { if (m_value != value) { m_value = value; Update(); } }
    operator Type const () const                 { return m_value; }

    void Reset(Type const value = Type())        { m_value = value; gl_State::Reset(state); }
    bool Check()                                 { return gl_State::Check(state); }
    void Update()                                { gl_State::Update(state); }

protected:
    Type m_value;
};

template< typename Type, u32 state >
class gl_StateProperty2 : protected gl_State
{
public:
    void operator () (typename Type::Value1 value1,
                      typename Type::Value2 value2) { this->operator = (Type(value1, value2)); }
    void operator = (Type const value)              { if (m_value != value) { m_value = value; Update(); } }
    operator Type const &() const                   { return m_value; }

    void Reset(typename Type::Value1 value1,
               typename Type::Value2 value2)        { this->Reset(Type(value1, value2)); }
    void Reset(Type const value = Type())           { m_value = value; gl_State::Reset(state); }
    bool Check()                                    { return gl_State::Check(state); }
    void Update()                                   { gl_State::Update(state); }

protected:
    Type m_value;
};

template< typename Type, u32 state >
class gl_StateProperty3 : protected gl_State 
{
public:
    void operator () (typename Type::Value1 value1,
                      typename Type::Value2 value2,
                      typename Type::Value3 value3) { this->operator = (Type(value1, value2, value3)); }
    void operator = (Type const value)              { if (m_value != value) { m_value = value; Update(); } }
    operator Type const &() const                   { return m_value; }

    void Reset(typename Type::Value1 value1,
               typename Type::Value2 value2,
               typename Type::Value3 value3)        { this->Reset(Type(value1, value2, value3)); }
    void Reset(Type const value = Type())           { m_value = value; gl_State::Reset(state); }
    bool Check()                                    { return gl_State::Check(state); }
    void Update()                                   { gl_State::Update(state); }

protected:
    Type m_value;
};

template< typename Type, u32 state >
class gl_StateProperty4 : protected gl_State 
{
public:
    void operator () (typename Type::Value1 value1,
                      typename Type::Value2 value2,
                      typename Type::Value3 value3,
                      typename Type::Value4 value4) { this->operator = (Type(value1, value2, value3, value4)); }
    void operator = (Type const value)              { if (m_value != value) { m_value = value; Update(); } }
    operator Type const &() const                   { return m_value; }
    
    void Reset(typename Type::Value1 value1,
               typename Type::Value2 value2,
               typename Type::Value3 value3,
               typename Type::Value4 value4)        { this->Reset(Type(value1, value2, value3, value4)); }
    void Reset(Type const value = Type())           { m_value = value; gl_State::Reset(state); }
    bool Check()                                    { return gl_State::Check(state); }
    void Update()                                   { gl_State::Update(state); }

protected:
    Type m_value;
};

template< typename Type, u32 state >
class gl_StateProperty5 : protected gl_State 
{
public:
    void operator () (typename Type::Value1 value1,
                      typename Type::Value2 value2, 
                      typename Type::Value3 value3,
                      typename Type::Value4 value4,
                      typename Type::Value5 value5) { this->operator = (Type(value1, value2, value3, value4, value5)); }
    void operator = (Type const value)              { if (m_value != value) { m_value = value; Update(); } }
    operator Type const &() const                   { return m_value; }

    void Reset(typename Type::Value1 value1,
               typename Type::Value2 value2,
               typename Type::Value3 value3,
               typename Type::Value4 value4,
               typename Type::Value5 value5)        { this->Reset(Type(value1, value2, value3, value4, value5)); }
    void Reset(Type const value = Type())           { m_value = value; gl_State::Reset(state); }
    bool Check()                                    { return gl_State::Check(state); }
    void Update()                                   { gl_State::Update(state); }

protected:
    Type m_value;
};

class gl_Fogging : protected gl_State
{
public:
    __forceinline void Reset()
    {
        enabled.Reset(false);

        gl_Core::Disable(FOG);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(FOG);
            }
            else
            {
                gl_Core::Disable(FOG);
            }
        }

        if (mode.Check())
        {
            Fogi(FOG_MODE, mode);
        }

        if (end.Check())
        {
            Fogf(FOG_END, end);
        }

        if (distance.Check())
        {
            f32 start = end - ((distance != 0.0f) ? (1.0f / distance) : 0.0f);
            Fogf(FOG_START, start);
        }

        if (color.Check())
        {
            f32 rgba[4] = { ((color >> 0) & 255) / 255.0f, ((color >> 8) & 255) / 255.0f, ((color >> 16) & 255) / 255.0f, 1.0f };

            Fogfv(FOG_COLOR, rgba);
        }
    }

    gl_StateProperty1< GLenum, FoggingMode     > mode;
    gl_StateProperty1< f32,    FoggingEnd      > end;
    gl_StateProperty1< f32,    FoggingDistance > distance;
    gl_StateProperty1< u32,    FoggingColor    > color;
    gl_StateProperty1< bool,   FoggingEnabled  > enabled;
}; 

class gl_ScissorTest : protected gl_State
{
public:
    struct Area
    {
        typedef u32 Value1, Value2, Value3, Value4;

        Area(u32 x = u32(), u32 y = u32(), u32 w = u32(), u32 h = u32()) : x(x), y(y), w(w), h(h) {}

        void operator () (u32 x, u32 y, u32 w, u32 h) { this->x = x; this->y = y; this->w = w; this->h = h; }
        bool operator != (Area const &area)           { return (area.x != x) || (area.y != y) || (area.w != w) || (area.h != h); }

        u32 x, y, w, h;
    };

    __forceinline void Reset()
    {
        area.Reset(0, 0, 0, 0);
        enabled.Reset(false);

        gl_Core::Disable(SCISSOR_TEST);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(SCISSOR_TEST);
            }
            else
            {
                gl_Core::Disable(SCISSOR_TEST);
            }
        }

        if (area.Check())
        {
            gl_Core::Scissor(GLint(Area(area).x), GLint(Area(area).y), GLsizei(Area(area).w), GLsizei(Area(area).h));
        }
    }

    gl_StateProperty4< Area, ScissorArea    > area;
    gl_StateProperty1< bool, ScissorEnabled > enabled;
}; 

class gl_DepthBoundsTest : protected gl_State
{
public:
    struct Range
    {
        typedef u32 Value1, Value2;

        Range(u32 minz = u32(), u32 maxz = u32()) : minz(minz), maxz(maxz) {}

        void operator () (u32 minz, u32 maxz) { this->minz = minz; this->maxz = maxz; }
        bool operator != (Range const &range) { return (range.minz != minz) || (range.maxz != maxz); }

        u32 minz, maxz;
    };

    __forceinline void Reset()
    {
        range.Reset(0, 0);
        enabled.Reset(false);

        gl_Core::Disable(DEPTH_BOUNDS_TEST);
    }

    __forceinline void Apply()
    {
        if (enabled.Check() && gl_Core::depth_bounds_test)
        {
            if (enabled)
            {
                gl_Core::Enable(DEPTH_BOUNDS_TEST);
            }
            else
            {
                gl_Core::Disable(DEPTH_BOUNDS_TEST);
            }
        }

        if (range.Check() && gl_Core::depth_bounds_test)
        {
            gl_Core::DepthBounds(GLclampd(Range(range).minz), GLclampd(Range(range).maxz));
        }
    }

    gl_StateProperty2< Range, DepthBoundsTestBounds > range;
    gl_StateProperty1< bool,  DepthBoundsTestBounds > enabled;
}; 

class gl_AlphaTest : protected gl_State
{
public:
    struct Function
    {
        typedef u8 Value1;
        typedef u8 Value2;
        typedef u8 Value3;

        Function(u8 atf = u8(), u8 aref = u8(), u8 amsk = u8()) : atf(atf), aref(aref), amsk(amsk) {}

        void operator () (u8 atf, u8 aref, u8 amsk) { this->atf = atf; this->aref = aref; this->amsk = amsk; }
        bool operator != (Function const &function) { return (function.atf != atf) || (function.aref != aref) /* || (function.amsk != amsk) */; }

        u8 atf;
        u8 aref;
        u8 amsk;
    };

    __forceinline void Reset()
    {
        function.Reset(0, 0, 0);
        enabled.Reset(false);

        gl_Core::Disable(ALPHA_TEST);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(ALPHA_TEST);
            }
            else
            {
                gl_Core::Disable(ALPHA_TEST);
            }
        }

        if (function.Check())
        {
            gl_Core::AlphaFunc(TFUNC(Function(function).atf), GLclampf(Function(function).aref)/255.0f);
        }
    }

    gl_StateProperty3< Function,  AlphaTestFunction > function;
    gl_StateProperty1< bool,      AlphaTestEnabled  > enabled;
}; 

class gl_StencilTest : protected gl_State
{
public:
    struct Function
    {
        typedef u8 Value1;
        typedef u8 Value2;
        typedef u8 Value3;

        Function(u8 stf = u8(), u8 sref = u8(), u8 smsk = u8()) : stf(stf), sref(sref), smsk(smsk) {}

        void operator () (u8 stf, u8 sref, u8 smsk) { this->stf = stf; this->sref = sref; this->smsk = smsk; }
        bool operator != (Function const &function) { return (function.stf != stf) || (function.sref != sref) || (function.smsk != smsk); }

        u8 stf;
        u8 sref;
        u8 smsk;
    };

    struct Operation
    {
        typedef u8 Value1;
        typedef u8 Value2;
        typedef u8 Value3;

        Operation(u8 sfail = u8(), u8 zfail = u8(), u8 zpass = u8()) : sfail(sfail), zfail(zfail), zpass(zpass) {}

        void operator () (u8 sfail, u8 zfail, u8 zpass) { this->sfail = sfail; this->zfail = zfail; this->zpass = zpass; }
        bool operator != (Operation const &operation) { return (operation.sfail != sfail) || (operation.zfail != zfail) || (operation.zpass != zpass); }

        u8 sfail;
        u8 zfail;
        u8 zpass;
    };

    static __forceinline GLenum const SOP(u8 index)
    {
        assert(index < 8);
        static GLenum const translate[8] = { KEEP, ZERO, REPLACE, INVERT, INCR, DECR, KEEP, KEEP };
        return translate[index];
    }

    __forceinline void Reset()
    {
        function.Reset(0, 0, 0);
        operation.Reset(0, 0, 0);
        enabled.Reset(false);

        gl_Core::Disable(STENCIL_TEST);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(STENCIL_TEST);
            }
            else
            {
                gl_Core::Disable(STENCIL_TEST);
            }
        }

        if (function.Check())
        {
            gl_Core::StencilFunc(TFUNC(Function(function).stf), GLint(Function(function).sref), GLuint(Function(function).smsk));
        }

        if (operation.Check())
        {
            gl_Core::StencilOp(SOP(Operation(operation).sfail), SOP(Operation(operation).zfail), SOP(Operation(operation).zpass));
        }
    }

    gl_StateProperty3< Function,  StencilTestFunction  > function;
    gl_StateProperty3< Operation, StencilTestOperation > operation;
    gl_StateProperty1< bool,      StencilTestEnabled   > enabled;
}; 


class gl_DepthTest : protected gl_State
{
public:
    __forceinline void Reset()
    {
        enabled.Reset(false);
        function.Reset();

        gl_Core::Disable(DEPTH_TEST);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(DEPTH_TEST);
            }
            else
            {
                gl_Core::Disable(DEPTH_TEST);
            }
        }

        if (function.Check())
        {
            gl_Core::DepthFunc(TFUNC(function));
        }
    }

    gl_StateProperty1< u32,  DepthTestFunc    > function;
    gl_StateProperty1< bool, DepthTestEnabled > enabled;
}; 


class gl_Blending : protected gl_State
{
public:
    struct Equation
    {
        typedef u8  Value1;
        typedef u8  Value2;
        typedef u8  Value3;
        typedef u32 Value4;
        typedef u32 Value5;

        Equation(u8 a = u8(), u8 b = u8(), u8 equ = u8(), u32 fixa = u32(), u32 fixb = u32()) : a(a), b(b), equ(equ), fixa(fixa), fixb(fixb) {}

        void operator () (u8 a, u8 b, u8 equ, u32 fixa, u32 fixb) { this->a = a; this->b = b; this->equ = equ; this->fixa = fixa; this->fixb = fixb; }
        bool operator != (Equation const &equation) { return (equation.a != a) || (equation.b != b) || (equation.equ != equ) || (equation.fixa != fixa) || (equation.fixb != fixb); }

        u8  a;
        u8  b;
        u8  equ;
        u32 fixa;
        u32 fixb;
    };

    static __forceinline GLenum const EQU(u8 index)
    {
        assert(index < 8);
        static GLenum const translate[8] = { GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX, GL_FUNC_ADD, GL_FUNC_ADD, GL_FUNC_ADD };
        return translate[index];
    }

    static __forceinline GLenum const FIX(u32 color)
    {
        switch (color & 0xFFFFFF)
        {
        case 0x000000:
            return ZERO;
        case 0xFFFFFF:
            return ONE;
        default:
            gl_Core::BlendColor(GLfloat((color >> 0) & 255)/255.0f, GLfloat((color >> 8) & 255)/255.0f, GLfloat((color >> 12) & 255)/255.0f, 1.0f); break;
        }
        return GL_CONSTANT_COLOR;
    }

    __forceinline void Reset()
    {
        equation.Reset(0, 0, 0, 0, 0);
        enabled.Reset(false);

        gl_Core::Disable(BLEND);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(BLEND);
            }
            else
            {
                gl_Core::Disable(BLEND);
            }
        }

        if (equation.Check())
        {
            u32	a = ZERO;
            u32 b = ONE;
            u32 fixa = Equation(equation).fixa;
            u32 fixb = Equation(equation).fixb;

            glBlendEquationSeparate(EQU(Equation(equation).equ), GL_FUNC_ADD);

            switch (Equation(equation).a)
            {
            case  0: a = DST_COLOR;			  break;
            case  1: a = ONE_MINUS_DST_COLOR; break;
            case  2: a = SRC_ALPHA;			  break;
            case  3: a = ONE_MINUS_SRC_ALPHA; break;
            case  4: a = DST_ALPHA;			  break;
            case  5: a = ONE_MINUS_DST_ALPHA; break;
            case  6: a = SRC_ALPHA;			  break;
            case  7: a = ONE_MINUS_SRC_ALPHA; break;
            case  8: a = DST_ALPHA;			  break;
            case  9: a = ONE_MINUS_DST_ALPHA; break;
            case 10: a = FIX(fixa);           break;
            default: errorf(Renderer, "Unsupported src blending mode");
            }

            switch (Equation(equation).b) 
            {
            case  0: b = SRC_COLOR;			  break;
            case  1: b = ONE_MINUS_SRC_COLOR; break;
            case  2: b = SRC_ALPHA;           break;
            case  3: b = ONE_MINUS_SRC_ALPHA; break;
            case  4: b = DST_ALPHA;           break;
            case  5: b = ONE_MINUS_DST_ALPHA; break;
            case  6: b = SRC_ALPHA;           break;
            case  7: b = ONE_MINUS_SRC_ALPHA; break;
            case  8: b = DST_ALPHA;           break;
            case  9: b = ONE_MINUS_DST_ALPHA; break;
            case 10: b = FIX(fixb);           break;
            default: errorf(Renderer, "Unsupported dst blending mode");
            }

            glBlendFuncSeparate(a, b, GL_ONE, GL_ZERO); 
        }

    }

    gl_StateProperty5< Equation,  BlendingEquation > equation;
    gl_StateProperty1< bool,      BlendingEnabled  > enabled;
}; 


class gl_LogicalOperation : protected gl_State
{
public:
    static __forceinline GLenum const LOP(u8 index)
    {
        assert(index < 16);
        static GLenum const translate[16] = { CLEAR, AND, AND_REVERSE, COPY, AND_INVERTED, NOOP, XOR, OR, NOR, EQUIV, INVERT, OR_REVERSE, COPY_INVERTED, OR_INVERTED, NAND, SET };
        return translate[index];
    }

    __forceinline void Reset()
    {
        function.Reset(0);
        enabled.Reset(false);

        gl_Core::Disable(COLOR_LOGIC_OP);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(COLOR_LOGIC_OP);
            }
            else
            {
                gl_Core::Disable(COLOR_LOGIC_OP);
            }
        }

        if (function.Check())
        {
            gl_Core::LogicOp(LOP(function));
        }
    }

    gl_StateProperty1< u8,   LogicalOperationFunction > function;
    gl_StateProperty1< bool, LogicalOperationEnabled  > enabled;
}; 


class gl_Dithering : protected gl_State
{
public:
    __forceinline void Reset()
    {
        enabled.Reset(false);

        gl_Core::Disable(DITHER);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(DITHER);
            }
            else
            {
                gl_Core::Disable(DITHER);
            }
        }
    }

    gl_StateProperty1< bool, DitheringEnabled > enabled;
}; 

class gl_LineSmoothing : protected gl_State
{
public:
    __forceinline void Reset()
    {
        enabled.Reset(false);

        gl_Core::Disable(LINE_SMOOTH);
    }

    __forceinline void Apply()
    {
        if (enabled.Check())
        {
            if (enabled)
            {
                gl_Core::Enable(LINE_SMOOTH);
            }
            else
            {
                gl_Core::Disable(LINE_SMOOTH);
            }
        }
    }

    gl_StateProperty1< bool, LineSmoothEnabled > enabled;
}; 

weaksymbol u8 gl_State::m_active_changes[gl_State::StateCount];
weaksymbol u8 gl_State::m_changes[gl_State::StateCount];

weaksymbol gl_Fogging          theFogging;
weaksymbol gl_ScissorTest      theScissorTest;
weaksymbol gl_DepthBoundsTest  theDepthBoundsTest;
weaksymbol gl_AlphaTest        theAlphaTest;
weaksymbol gl_StencilTest      theStencilTest;
weaksymbol gl_DepthTest        theDepthTest;
weaksymbol gl_Blending         theBlending;
weaksymbol gl_LogicalOperation theLogicalOperation;
weaksymbol gl_Dithering        theDithering;
weaksymbol gl_LineSmoothing    theLineSmoothing;

#endif // gl_States_h__
