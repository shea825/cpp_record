## 重构获得模式
* 寻找变化点，然后在变化点处应用设计模式，从而来更好地应对需求的变化
* 什么时候、什么地点应用设计模式 比 理解设计模式结构本身 更为重要

## 从封装变化角度对模式分类
* 组件协作 （主要通过晚期绑定，实现框架与应用程序之间的松耦合）
  * Template Method
  * Strategy
  * Observer/Event
* 单一职责
  * Decorator
  * Bridge
* 对象创建
  * Factory Method
  * Abstract Factory
  * Prototype
  * Builder
* 对象性能
  * Singleton
  * Flyweight
* 接口隔离
  * Facade
  * Proxy
  * Mediator
  * Adapter
* 状态变化
  * Memento
  * State
* 数据结构
  * Composite
  * Iterator
  * Chain of Responsibility
* 行为变化
  * Command
  * Visitor
* 领域问题
  * Interpreter

## 重构关键技法
* 静态 -> 动态
* 早绑定 -> 晚绑定
* 继承 -> 组合
* 编译时依赖 -> 运行时依赖
* 紧耦合 -> 松耦合