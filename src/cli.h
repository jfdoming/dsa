#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include <functional>

class CLI {
    public:
        class Status {
            public:
                enum class Type {
                    OKAY, IGNORE, EXIT
                };
                Status(Type type);
                Status(Type type, int code);

                operator int() const;
                Type type;
                int code;
        };

        CLI(std::string key);
        CLI(std::string key, std::vector<CLI *> children);
        virtual ~CLI();
        Status run(CLI *parent = nullptr);
        Status exec(std::string input, bool silent = true);

        void forEachChild(const std::function<void(CLI *)> &fn);
    protected:
        virtual Status beforeRun();
        virtual Status beforeRun(CLI *parent);
        virtual void eachRun();
        virtual void afterRun();
        virtual Status eachInput(std::string input);
        virtual bool eachFailedMatch(std::string input, bool silent = true);
    private:
        std::string key;
        std::vector<CLI *> children;
};

#endif
