/**
 * Class for variable declaration.
 */
class VarDeclStmt: public Stmt {
    public:
        VarDeclStmt(Token name, Expr* initializer, bool _mutable)
            : m_name{name}, m_initializer{initializer}, m_mutable{_mutable} { }

        // ...

        Token m_name;
        Expr* m_initializer;
        bool m_mutable;
};


